QuickMenu_EventScript_Main::
	multichoice 0, 0, MULTI_QUICK_MENU, FALSE
	switch VAR_RESULT
	case 0, QuickMenu_EventScript_Fly
	case 1, QuickMenu_EventScript_ToggleInfiniteRepel
	case 2, QuickMenu_EventScript_PokeVial
	case 3, QuickMenu_EventScript_PC
	case 4, QuickMenu_EventScript_Cancel
	case MULTI_B_PRESSED, QuickMenu_EventScript_Cancel
	end

QuickMenu_EventScript_Fly::
	specialvar VAR_RESULT, QuickMenu_CanFly
	goto_if_eq VAR_RESULT, FALSE, QuickMenu_EventScript_CantFlyHere
	special QuickMenu_Fly
	end

QuickMenu_EventScript_CantFlyHere::
	msgbox QuickMenu_Text_CantFlyHere
	closemessage
	end

QuickMenu_EventScript_ToggleInfiniteRepel::
	specialvar VAR_RESULT, QuickMenu_ToggleInfiniteRepel
	goto_if_eq VAR_RESULT, TRUE, QuickMenu_EventScript_InfiniteRepelOn
	msgbox QuickMenu_Text_InfiniteRepelOff
	closemessage
	end

QuickMenu_EventScript_InfiniteRepelOn::
	msgbox QuickMenu_Text_InfiniteRepelOn
	closemessage
	end

QuickMenu_EventScript_PokeVial::
	call Common_EventScript_OutOfCenterPartyHeal
	end

QuickMenu_EventScript_PC::
	goto EventScript_PC
	end

QuickMenu_EventScript_Cancel::
	end

QuickMenu_Text_CantFlyHere:
	.string "You can't FLY from here.$"

QuickMenu_Text_InfiniteRepelOn:
	.string "Infinite REPEL activated!$"

QuickMenu_Text_InfiniteRepelOff:
	.string "Infinite REPEL deactivated.$"
