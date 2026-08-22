#include "global.h"
#include "quick_menu.h"
#include "event_data.h"
#include "main.h"
#include "party_menu.h"
#include "region_map.h"
#include "constants/item.h"

u16 QuickMenu_CanFly(void)
{
    return SetUpFieldMove_Fly();
}

void QuickMenu_Fly(void)
{
    SetMainCallback2(CB2_OpenFlyMap);
}

u16 QuickMenu_ToggleInfiniteRepel(void)
{
    if (FlagGet(OW_FLAG_INFINITE_REPEL))
    {
        FlagClear(OW_FLAG_INFINITE_REPEL);
        VarSet(VAR_REPEL_STEP_COUNT, 0);
        return FALSE;
    }

    FlagSet(OW_FLAG_INFINITE_REPEL);
    VarSet(VAR_REPEL_STEP_COUNT, REPEL_LURE_MASK - 1);
    return TRUE;
}
