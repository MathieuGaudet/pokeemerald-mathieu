#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "event_data.h"
#include "caps.h"
#include "pokemon.h"
#include "constants/opponents.h"

struct LevelCapEntry
{
    bool32 (*IsCleared)(void);
    u32 cap;
};

static bool32 CapCheck_Badge01(void) { return FlagGet(FLAG_BADGE01_GET); }
static bool32 CapCheck_RustboroRival(void) { return FlagGet(FLAG_DEFEATED_RIVAL_RUSTBORO); }
static bool32 CapCheck_Badge02(void) { return FlagGet(FLAG_BADGE02_GET); }

static bool32 CapCheck_Route110Rival(void)
{
    return FlagGet(TRAINER_FLAGS_START + TRAINER_MAY_ROUTE_110_TREECKO)
        || FlagGet(TRAINER_FLAGS_START + TRAINER_MAY_ROUTE_110_TORCHIC)
        || FlagGet(TRAINER_FLAGS_START + TRAINER_MAY_ROUTE_110_MUDKIP)
        || FlagGet(TRAINER_FLAGS_START + TRAINER_BRENDAN_ROUTE_110_TREECKO)
        || FlagGet(TRAINER_FLAGS_START + TRAINER_BRENDAN_ROUTE_110_TORCHIC)
        || FlagGet(TRAINER_FLAGS_START + TRAINER_BRENDAN_ROUTE_110_MUDKIP);
}

static bool32 CapCheck_Badge03(void) { return FlagGet(FLAG_BADGE03_GET); }
static bool32 CapCheck_MtChimneyMagma(void) { return FlagGet(FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY); }
static bool32 CapCheck_Badge04(void) { return FlagGet(FLAG_BADGE04_GET); }
static bool32 CapCheck_Badge05(void) { return FlagGet(FLAG_BADGE05_GET); }

static bool32 CapCheck_Route119Rival(void)
{
    return FlagGet(TRAINER_FLAGS_START + TRAINER_MAY_ROUTE_119_TREECKO)
        || FlagGet(TRAINER_FLAGS_START + TRAINER_MAY_ROUTE_119_TORCHIC)
        || FlagGet(TRAINER_FLAGS_START + TRAINER_MAY_ROUTE_119_MUDKIP)
        || FlagGet(TRAINER_FLAGS_START + TRAINER_BRENDAN_ROUTE_119_TREECKO)
        || FlagGet(TRAINER_FLAGS_START + TRAINER_BRENDAN_ROUTE_119_TORCHIC)
        || FlagGet(TRAINER_FLAGS_START + TRAINER_BRENDAN_ROUTE_119_MUDKIP);
}

static bool32 CapCheck_Badge06(void) { return FlagGet(FLAG_BADGE06_GET); }

static bool32 CapCheck_LilycoveRival(void)
{
    return FlagGet(TRAINER_FLAGS_START + TRAINER_MAY_LILYCOVE_TREECKO)
        || FlagGet(TRAINER_FLAGS_START + TRAINER_MAY_LILYCOVE_TORCHIC)
        || FlagGet(TRAINER_FLAGS_START + TRAINER_MAY_LILYCOVE_MUDKIP)
        || FlagGet(TRAINER_FLAGS_START + TRAINER_BRENDAN_LILYCOVE_TREECKO)
        || FlagGet(TRAINER_FLAGS_START + TRAINER_BRENDAN_LILYCOVE_TORCHIC)
        || FlagGet(TRAINER_FLAGS_START + TRAINER_BRENDAN_LILYCOVE_MUDKIP);
}

static bool32 CapCheck_Badge07(void) { return FlagGet(FLAG_BADGE07_GET); }
static bool32 CapCheck_SeafloorCavern(void) { return FlagGet(FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN); }
static bool32 CapCheck_Badge08(void) { return FlagGet(FLAG_BADGE08_GET); }
static bool32 CapCheck_WallyVictoryRoad(void) { return FlagGet(FLAG_DEFEATED_WALLY_VICTORY_ROAD); }
static bool32 CapCheck_Champion(void) { return FlagGet(FLAG_IS_CHAMPION); }

u32 GetCurrentLevelCap(void)
{
    static const struct LevelCapEntry sLevelCapTable[] =
    {
        {CapCheck_Badge01,          15}, // Pre-Roxanne
        {CapCheck_RustboroRival,    20}, // Pre-Rustboro Rival Fight
        {CapCheck_Badge02,          25}, // Pre-Brawly
        {CapCheck_Route110Rival,    32}, // Pre-Route 110 Rival Fight
        {CapCheck_Badge03,          34}, // Pre-Wattson
        {CapCheck_MtChimneyMagma,   44}, // Pre-Mt. Chimney Magma Bosses
        {CapCheck_Badge04,          47}, // Pre-Flannery
        {CapCheck_Badge05,          59}, // Pre-Norman
        {CapCheck_Route119Rival,    64}, // Pre-Route 119 Rival Fight
        {CapCheck_Badge06,          68}, // Pre-Winona
        {CapCheck_LilycoveRival,    71}, // Pre-Rival Battle in Lilycove
        {CapCheck_Badge07,          76}, // Pre-Tate and Liza
        {CapCheck_SeafloorCavern,   80}, // Pre-Seafloor Cavern
        {CapCheck_Badge08,          82}, // Pre-Juan
        {CapCheck_WallyVictoryRoad, 84}, // Pre-Wally in Victory Road
        {CapCheck_Champion,         85}, // Pre-Champion
    };

    u32 i;

    if (B_LEVEL_CAP_TYPE == LEVEL_CAP_FLAG_LIST)
    {
        for (i = 0; i < ARRAY_COUNT(sLevelCapTable); i++)
        {
            if (!sLevelCapTable[i].IsCleared())
                return sLevelCapTable[i].cap;
        }
    }
    else if (B_LEVEL_CAP_TYPE == LEVEL_CAP_VARIABLE)
    {
        return VarGet(B_LEVEL_CAP_VARIABLE);
    }

    return MAX_LEVEL;
}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };
    static const u32 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

    u32 levelDifference;
    u32 currentLevelCap = GetCurrentLevelCap();

    if (B_EXP_CAP_TYPE == EXP_CAP_NONE)
        return expValue;

    if (level < currentLevelCap)
    {
        if (B_LEVEL_CAP_EXP_UP)
        {
            levelDifference = currentLevelCap - level;
            if (levelDifference > ARRAY_COUNT(sExpScalingUp) - 1)
                return expValue + (expValue / sExpScalingUp[ARRAY_COUNT(sExpScalingUp) - 1]);
            else
                return expValue + (expValue / sExpScalingUp[levelDifference]);
        }
        else
        {
            return expValue;
        }
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_HARD)
    {
        return 0;
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_SOFT)
    {
        levelDifference = level - currentLevelCap;
        if (levelDifference > ARRAY_COUNT(sExpScalingDown) - 1)
            return expValue / sExpScalingDown[ARRAY_COUNT(sExpScalingDown) - 1];
        else
            return expValue / sExpScalingDown[levelDifference];
    }
    else
    {
       return expValue;
    }
}

u32 GetCurrentEVCap(void)
{
    static const u16 sEvCapFlagMap[][2] = {
        // Define EV caps for each milestone
        {FLAG_BADGE01_GET, MAX_TOTAL_EVS *  1 / 17},
        {FLAG_BADGE02_GET, MAX_TOTAL_EVS *  3 / 17},
        {FLAG_BADGE03_GET, MAX_TOTAL_EVS *  5 / 17},
        {FLAG_BADGE04_GET, MAX_TOTAL_EVS *  7 / 17},
        {FLAG_BADGE05_GET, MAX_TOTAL_EVS *  9 / 17},
        {FLAG_BADGE06_GET, MAX_TOTAL_EVS * 11 / 17},
        {FLAG_BADGE07_GET, MAX_TOTAL_EVS * 13 / 17},
        {FLAG_BADGE08_GET, MAX_TOTAL_EVS * 15 / 17},
        {FLAG_IS_CHAMPION, MAX_TOTAL_EVS},
    };

    if (B_EV_CAP_TYPE == EV_CAP_FLAG_LIST)
    {
        for (u32 evCap = 0; evCap < ARRAY_COUNT(sEvCapFlagMap); evCap++)
        {
            if (!FlagGet(sEvCapFlagMap[evCap][0]))
                return sEvCapFlagMap[evCap][1];
        }
    }
    else if (B_EV_CAP_TYPE == EV_CAP_VARIABLE)
    {
        return VarGet(B_EV_CAP_VARIABLE);
    }
    else if (B_EV_CAP_TYPE == EV_CAP_NO_GAIN)
    {
        return 0;
    }

    return MAX_TOTAL_EVS;
}
