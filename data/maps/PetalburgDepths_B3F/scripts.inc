PetalburgDepths_B3F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PetalburgDepths_B3F_OnLoad
	.byte 0

PetalburgDepths_B3F_OnLoad:
	call_if_set FLAG_DEFEATED_PETALBURG_DEPTHS_B3F, PetalburgDepths_B3F_EventScript_OpenGate
	end

PetalburgDepths_B3F_EventScript_OpenGate::
	setmetatile 6, 1, METATILE_EliteFour_OpenDoor_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoor_Opening, FALSE
	special DrawWholeMapView
	return

PetalburgDepths_B3F_EventScript_Boss::
	trainerbattle_single TRAINER_PETALBURG_DEPTHS_BOSS3, PetalburgDepths_B3F_Text_BossIntro, PetalburgDepths_B3F_Text_BossDefeat, PetalburgDepths_B3F_EventScript_BossWon
	msgbox PetalburgDepths_B3F_Text_BossPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgDepths_B3F_EventScript_BossWon::
	setflag FLAG_DEFEATED_PETALBURG_DEPTHS_B3F
	call PetalburgDepths_B3F_EventScript_OpenGate
	msgbox PetalburgDepths_B3F_Text_BossPostBattle, MSGBOX_AUTOCLOSE
	release
	end

PetalburgDepths_B3F_Text_BossIntro:
	.string "MORWENNA: Mm… fresh company.\n"
	.string "It gets so quiet down here.\p"
	.string "Let's not be quiet anymore.$"

PetalburgDepths_B3F_Text_BossDefeat:
	.string "MORWENNA: Heh… the shadows favor\n"
	.string "you today.$"

PetalburgDepths_B3F_Text_BossPostBattle:
	.string "MORWENNA: Go on ahead. Whatever\n"
	.string "you find in the dark past here…\l"
	.string "it's yours.$"

PetalburgDepths_B3F_EventScript_WildPatch::
	lock
	faceplayer
	msgbox PetalburgDepths_B3F_Text_WildPatch, MSGBOX_DEFAULT
	setwildbattle SPECIES_RIOLU, 28
	waitse
	playmoncry SPECIES_RIOLU, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	release
	end

PetalburgDepths_B3F_Text_WildPatch:
	.string "Something rustles in the debris\n"
	.string "here…$"
