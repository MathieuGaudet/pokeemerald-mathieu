# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project overview

This is **pokeemerald-expansion** (RHH), a GBA ROM hack *base* built on top of pret's `pokeemerald` decompilation. It is not a playable game on its own — it's a toolkit/engine that ROM hack developers build on. The codebase is C (targeting `arm-none-eabi-gcc`, "modern" toolchain only — legacy `agbcc` support was removed) plus hand-written ARM/THUMB assembly, and includes an extensive battle/overworld feature set (Tera types, Gigantamax, Gen 1–9 species data, etc.) controlled almost entirely through compile-time configs in `include/config/*.h`.

Current branch `ai-experiment` is a personal experimentation branch off this base, per the user.

## General rules

- Do not modify files unless explicitly asked.
- Before making a change, inspect the existing implementation and follow
  established project conventions.
- Prefer the smallest change that accomplishes the requested feature.
- Do not rewrite or refactor unrelated code.
- Do not introduce new dependencies unless necessary.
- Do not modify generated files unless the project requires it.
- Do not modify upstream project functionality unnecessarily.

## Git

- Never commit changes unless explicitly asked.
- Never push changes unless explicitly asked.
- Before making significant changes, explain which files you expect to modify.
- Keep changes focused and easy to review.

## Build commands

```sh
make -j$(nproc)          # default build (equivalent to `make modern`)
make debug                # -Og / -g, DEBUG=1
make release               # -DNDEBUG -DRELEASE, LTO by default (config.mk: USE_LTO_ON_RELEASE)
make firered / make leafgreen   # alternate BUILD variants
make compare                # verifies the built ROM's SHA1 against rom.sha1
```

The ROM output is `pokeemerald.gba`. To use a non-devkitARM toolchain, override `TOOLCHAIN=/path/to/toolchain` (must contain a `bin` subdir).

## Test commands

Tests are C-based, driven through an mGBA headless ROM runner (`tools/`, `TESTELF`/`HEADLESSELF` targets in `Makefile`). Test sources live under `test/` (mirrors `test/battle/{ability,move_effect,item_effect,ai,...}`, `test/compression`, etc.).

```sh
make check -j$(nproc)                 # run the full test suite
make check TESTS="Spikes"             # run only tests whose name matches "Spikes"
make pokeemerald-test.elf TESTS="Spikes"   # build a .elf loadable in mGBA to inspect specific tests visually
```

Full guide: `docs/tutorials/how_to_testing_system.md`. Tests use a `GIVEN { PLAYER(...); OPPONENT(...); } WHEN { TURN { MOVE(...); } } SCENE { ANIMATION(...); MESSAGE(...); STATUS_ICON(...); }` DSL (see `SINGLE_BATTLE_TEST`, `DOUBLE_BATTLE_TEST` macros). `ASSUMPTIONS`/`ASSUME` document *why* a test's premise holds (e.g. a move's effect) and cause tests to skip rather than fail if the underlying data changes — write new tests to skip gracefully rather than hard-fail when someone reconfigures game data. Name related tests with a shared prefix so they can be targeted via `TESTS="<prefix>"`.

## Architecture

The dominant pattern throughout this codebase: **data is authored in a friendlier source format, then a small custom C/C++ tool in `tools/` compiles it into generated `.inc`/`.h` files that get built into the ROM.** Generated files are stamped "DO NOT MODIFY THIS FILE" — always edit the source form.

### Trainers
- Source: `src/data/trainers.party` (Pokémon-Showdown-export-style text), compiled by `tools/trainerproc` into generated `src/data/trainers.h`.
- Runtime type: `struct Trainer` (`include/data.h`) — class, pic, AI flags (`AI_FLAG_*` in `include/constants/battle_ai.h`), battle type, and a `party` array of `struct TrainerMon` (species/level/IVs/EVs/moves/item/ability/shininess/tera type). Supports pool-based party randomization (`poolSize`/`poolPickIndex`).

### Pokémon data
- Species data: `src/data/pokemon/species_info/gen_N_families.h` build up `gSpeciesInfo[]` (`struct SpeciesInfo`, `include/pokemon.h`) — base stats, types, abilities, egg groups, and pointers into separate learnset/egg-move/evolution tables under `src/data/pokemon/`.
- Runtime representation is **not** the same struct: `struct Pokemon` wraps `struct BoxPokemon`, which stores `personality`/`otId` plus an encrypted, personality-shuffled union of 4 substructures (growth/moves/EVs-contest/IVs-misc) — this reproduces the real Gen III save format bit-for-bit (`EncryptBoxMon`/`DecryptBoxMon` in `src/pokemon.c`). In-battle live stats/state use a separate `struct BattlePokemon` (`gBattleMons[]`, `include/pokemon.h`/`include/battle.h`), distinct from party `struct Pokemon`.

### Maps and NPCs
- Each map is a directory `data/maps/<MapName>/` authored (via Porymap) as `map.json` (header, connections, object/warp/coord/bg events) plus `scripts.inc`. `tools/mapjson` compiles `map.json` + the global `data/maps/map_groups.json`/`data/layouts/layouts.json` into generated `header.inc`/`connections.inc`/`events.inc` and `include/constants/map_groups.h`.
- NPCs are `object_events` entries in `map.json` (graphics id, position, `movement_type`, trainer battle config, interaction script, hide-flag). `movement_type` indexes a function-pointer table in `src/event_object_movement.c` that drives per-frame NPC movement/AI.
- Runtime: `gMapGroups[group][num]` → `struct MapHeader` → layout/events/scripts pointers.

### Scripting (two separate bytecode VMs)
- **Overworld field scripts**: authored per-map in `scripts.inc` as hand-written assembly-macro bytecode (Poryscript tooling exists — `tools/poryscript` compiles `.pory` → `.inc` — but is effectively unused in this repo; virtually everything is raw `.inc`). Interpreted by `RunScriptCommand()` in `src/script.c`, dispatching through `gScriptCmdTable` (`data/script_cmd_table.inc`) to handlers in `src/scrcmd.c`.
- **Battle scripts**: a structurally identical but entirely separate bytecode VM for move effects. `gMovesInfo[move].effect` selects a script via `gBattleMoveEffects[]` (`src/data/battle_move_effects.h`); the script itself lives in `data/battle_scripts_*.s` and runs through `RunBattleScriptCommands()` indexing `gBattleScriptingCommandsTable[]` (`src/battle_script_commands.c`, ~14k lines of `Cmd_*` handlers).

### Battle system
- Core state machine in `src/battle_main.c`, driven by a reassignable function pointer (`gBattleMainFunc`) stepping through intro → action selection (`HandleTurnActionSelectionState`) → turn ordering (`SetActionsAndBattlersTurnOrder`) → turn execution (`RunTurnActionsFunctions`, dispatches to `HandleAction_UseMove`/`HandleAction_Switch`/etc. in `src/battle_util.c`) → end-of-turn (`BattleTurnPassed`, `src/battle_end_turn.c`).
- Move data: `gMovesInfo[]` (`struct MoveInfo`, `include/move.h`) in `src/data/moves_info.h` — power/accuracy/pp/type/target/priority, `additionalEffects`, and dozens of boolean flag bits (`makesContact`, `soundMove`, etc.) consumed throughout `battle_util.c`/`battle_script_commands.c`.

### Config system
Feature toggles live under `include/config/*.h` (`ai.h`, `battle.h`, `pokemon.h`, `overworld.h`, `debug.h`, etc.) as `B_*`/`P_*`-style `#define`s, generation-gated (e.g. `B_UPDATED_MOVE_DATA >= GEN_6`). Per `docs/STYLEGUIDE.md`: check configs in normal control flow rather than early-returning inside `#ifdef` blocks; save-modifying functionality must be config-gated and off by default; QoL/modern-Pokémon-accurate configs default on; everything else defaults off.

### Build system
- `Makefile` + included `.mk` files (`graphics_file_rules.mk`, `map_data_rules.mk`, `json_data_rules.mk`, `trainer_rules.mk`, `audio_rules.mk`, `make_tools.mk`, `config.mk`). Custom tools in `tools/` (built by `make_tools.mk`) handle all data/asset compilation: `gbagfx` (graphics + compression), `preproc` (charmap/string preprocessing piped between `cpp` and `cc1`), `scaninc` (dependency scanning), `mapjson`, `jsonproc`, `trainerproc`, `poryscript`, `mid2agb`/`wav2agb`, `ramscrgen`.
- Linked via `ld_script_modern.ld`; final `.gba` produced via `gbafix`/`objcopy`.
- Directories: `src/` (C, some `.s`), `asm/` (hand-written ASM), `data/` (scripts, map/battle script bytecode, event/map data), `include/` (headers + generated constants), `graphics/` (source art), `sound/` (MIDI/WAV), `test/` (battle/compression test suite).

## Code style (see `docs/STYLEGUIDE.md` for full detail)

- `PascalCase` for functions/structs, `camelCase` for variables/fields, `CAPS_WITH_UNDERSCORES` for macros/constants/enums. Globals prefixed `g`, statics prefixed `s`.
- 4 spaces (no tabs) in `.c`/`.h`; tabs in `.s`/`.inc`.
- Opening braces on their own line; `if`/`else` chains use braces only when any condition or block spans multiple lines.
- Avoid magic numbers — use named constants/enums; use the enum type (not a bare integer type) for enum-valued function parameters.
- New functionality should be minimally invasive to existing files; isolate large additions into their own files. Unused-but-intentionally-present functions/data are marked `UNUSED`.

## Branching (from `CONTRIBUTING.md`)

Upstream uses `master` (bugfixes only) vs `upcoming` (new functionality) as target branches for PRs against `rh-hideout/pokeemerald-expansion`. Not directly relevant unless working against that upstream remote.

## Verification

After making code changes:
1. Build the project with `make -j$(nproc)`.
2. If the build fails, investigate and fix the problem.
3. Report what changed and whether the build succeeded.
4. Show me the relevant files/diff so I can review the work.

## Agent behavior

I am learning how agentic coding works.

When a task is ambiguous:
- explain your interpretation before making major changes.
- prefer asking rather than making a large assumption.

When investigating the codebase:
- search for existing examples before inventing new patterns.
- explain important discoveries so I can learn from them.