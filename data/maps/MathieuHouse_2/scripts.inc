MathieuHouse_2_MapScripts::
	.byte 0

MathieuHouse_2_EventScript_GiftPokemonGuy::
	lock
	faceplayer
	msgbox MathieuHouse_2_Text_GuyIntro, MSGBOX_DEFAULT
	goto MathieuHouse_2_EventScript_GiftMenu
	end

MathieuHouse_2_EventScript_GiftMenu::
	msgbox MathieuHouse_2_Text_WhichPokemon, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_MATHIEU_GIFT_MON, FALSE
	switch VAR_RESULT
	case 0, MathieuHouse_2_EventScript_ChooseStarly
	case 1, MathieuHouse_2_EventScript_ChooseHonedge
	case 2, MathieuHouse_2_EventScript_GuyFarewell
	case MULTI_B_PRESSED, MathieuHouse_2_EventScript_GuyFarewell
	end

MathieuHouse_2_EventScript_ChooseStarly::
	goto_if_set FLAG_RECEIVED_GIFT_STARLY, MathieuHouse_2_EventScript_AlreadyGotStarly
	msgbox MathieuHouse_2_Text_AboutStarly, MSGBOX_DEFAULT
	goto MathieuHouse_2_EventScript_GiveStarly
	end

MathieuHouse_2_EventScript_AlreadyGotStarly::
	msgbox MathieuHouse_2_Text_AlreadyGotStarly, MSGBOX_DEFAULT
	goto MathieuHouse_2_EventScript_GiftMenu
	end

MathieuHouse_2_EventScript_ChooseHonedge::
	goto_if_set FLAG_RECEIVED_GIFT_HONEDGE, MathieuHouse_2_EventScript_AlreadyGotHonedge
	msgbox MathieuHouse_2_Text_AboutHonedge, MSGBOX_DEFAULT
	goto MathieuHouse_2_EventScript_GiveHonedge
	end

MathieuHouse_2_EventScript_AlreadyGotHonedge::
	msgbox MathieuHouse_2_Text_AlreadyGotHonedge, MSGBOX_DEFAULT
	goto MathieuHouse_2_EventScript_GiftMenu
	end

MathieuHouse_2_EventScript_GuyFarewell::
	msgbox MathieuHouse_2_Text_GuyFarewell, MSGBOX_DEFAULT
	release
	end

MathieuHouse_2_EventScript_GiveStarly::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_STARLY
	givemon SPECIES_STARLY, 1, item=ITEM_STARAPTITE, nature=NATURE_JOLLY, abilityNum=1, move1=MOVE_CLOSE_COMBAT, move2=MOVE_DRAGON_ASCENT, move3=MOVE_ROOST, move4=MOVE_V_CREATE
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, MathieuHouse_2_EventScript_SendStarlyParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, MathieuHouse_2_EventScript_SendStarlyPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

MathieuHouse_2_EventScript_SendStarlyParty::
	call MathieuHouse_2_EventScript_ReceivedStarlyFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MathieuHouse_2_EventScript_ReceivedStarly
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto MathieuHouse_2_EventScript_ReceivedStarly
	end

MathieuHouse_2_EventScript_SendStarlyPC::
	call MathieuHouse_2_EventScript_ReceivedStarlyFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MathieuHouse_2_EventScript_StarlyTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto MathieuHouse_2_EventScript_StarlyTransferredToPC
	end

MathieuHouse_2_EventScript_StarlyTransferredToPC::
	call Common_EventScript_TransferredToPC
	goto MathieuHouse_2_EventScript_ReceivedStarly
	end

MathieuHouse_2_EventScript_ReceivedStarlyFanfare::
	playfanfare MUS_OBTAIN_ITEM
	bufferspeciesname STR_VAR_1, SPECIES_STARLY
	message gText_PlayerObtainedTheMon
	waitmessage
	waitfanfare
	return

MathieuHouse_2_EventScript_ReceivedStarly::
	setflag FLAG_RECEIVED_GIFT_STARLY
	goto MathieuHouse_2_EventScript_GiftMenu
	end

MathieuHouse_2_EventScript_GiveHonedge::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_HONEDGE
	givemon SPECIES_HONEDGE, 1, item=ITEM_LEFTOVERS, nature=NATURE_ADAMANT, shinyMode=SHINY_MODE_ALWAYS, move1=MOVE_SPECTRAL_THIEF, move2=MOVE_GIGATON_HAMMER, move3=MOVE_KINGS_SHIELD, move4=MOVE_SWORDS_DANCE
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, MathieuHouse_2_EventScript_SendHonedgeParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, MathieuHouse_2_EventScript_SendHonedgePC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

MathieuHouse_2_EventScript_SendHonedgeParty::
	call MathieuHouse_2_EventScript_ReceivedHonedgeFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MathieuHouse_2_EventScript_ReceivedHonedge
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto MathieuHouse_2_EventScript_ReceivedHonedge
	end

MathieuHouse_2_EventScript_SendHonedgePC::
	call MathieuHouse_2_EventScript_ReceivedHonedgeFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MathieuHouse_2_EventScript_HonedgeTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto MathieuHouse_2_EventScript_HonedgeTransferredToPC
	end

MathieuHouse_2_EventScript_HonedgeTransferredToPC::
	call Common_EventScript_TransferredToPC
	goto MathieuHouse_2_EventScript_ReceivedHonedge
	end

MathieuHouse_2_EventScript_ReceivedHonedgeFanfare::
	playfanfare MUS_OBTAIN_ITEM
	bufferspeciesname STR_VAR_1, SPECIES_HONEDGE
	message gText_PlayerObtainedTheMon
	waitmessage
	waitfanfare
	return

MathieuHouse_2_EventScript_ReceivedHonedge::
	setflag FLAG_RECEIVED_GIFT_HONEDGE
	additem ITEM_DUSK_STONE
	goto_if_eq VAR_RESULT, FALSE, MathieuHouse_2_EventScript_BagFullForDuskStone
	msgbox MathieuHouse_2_Text_ReceivedDuskStone, MSGBOX_DEFAULT
	goto MathieuHouse_2_EventScript_GiftMenu
	end

MathieuHouse_2_EventScript_BagFullForDuskStone::
	msgbox MathieuHouse_2_Text_BagFullDuskStone, MSGBOX_DEFAULT
	goto MathieuHouse_2_EventScript_GiftMenu
	end

MathieuHouse_2_Text_GuyIntro:
	.string "Hey, you're one of MATHIEU's friends,\n"
	.string "right?\p"
	.string "He asked me to hang onto a few of\n"
	.string "his favorite POKéMON and pass them\l"
	.string "along to trainers he trusts.$"

MathieuHouse_2_Text_WhichPokemon:
	.string "Which one would you like?$"

MathieuHouse_2_Text_AboutStarly:
	.string "STARLY's a scrappy little thing,\n"
	.string "but don't let that fool you.$"

MathieuHouse_2_Text_AboutHonedge:
	.string "HONEDGE's a bit unusual, if you\n"
	.string "catch my drift.$"

MathieuHouse_2_Text_AlreadyGotStarly:
	.string "I already gave you the STARLY.$"

MathieuHouse_2_Text_AlreadyGotHonedge:
	.string "I already gave you the HONEDGE.$"

MathieuHouse_2_Text_ReceivedDuskStone:
	.string "Oh, and here's a DUSK STONE to go\n"
	.string "along with it. MATHIEU insisted.$"

MathieuHouse_2_Text_BagFullDuskStone:
	.string "MATHIEU also wanted you to have a\n"
	.string "DUSK STONE, but your BAG's full.\p"
	.string "Come back for it later.$"

MathieuHouse_2_Text_GuyFarewell:
	.string "That's all I've got for now. Come\n"
	.string "back if MATHIEU sends more my way!$"

MathieuHouse_2_EventScript_DepthsSign::
	lockall
	msgbox MathieuHouse_2_Text_DepthsSign, MSGBOX_SIGN
	releaseall
	return

MathieuHouse_2_Text_DepthsSign:
	.string "A hatch is set into the floor\n"
	.string "beside this display… it looks like\l"
	.string "it leads deep underground.\p"
	.string "PETALBURG DEPTHS\n"
	.string "The way down gets tougher the\l"
	.string "farther you go.$"
