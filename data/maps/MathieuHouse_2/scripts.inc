MathieuHouse_2_MapScripts::
	.byte 0

MathieuHouse_2_EventScript_GiftPokemonGuy::
	lock
	faceplayer
	msgbox MathieuHouse_2_Text_GuyIntro, MSGBOX_DEFAULT
	goto_if_set FLAG_RECEIVED_GIFT_STARLY, MathieuHouse_2_EventScript_OfferHonedge
	msgbox MathieuHouse_2_Text_OfferStarly, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MathieuHouse_2_EventScript_OfferHonedge
	goto MathieuHouse_2_EventScript_GiveStarly
	end

MathieuHouse_2_EventScript_OfferHonedge::
	goto_if_set FLAG_RECEIVED_GIFT_HONEDGE, MathieuHouse_2_EventScript_GuyFarewell
	msgbox MathieuHouse_2_Text_OfferHonedge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MathieuHouse_2_EventScript_GuyFarewell
	goto MathieuHouse_2_EventScript_GiveHonedge
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
	goto MathieuHouse_2_EventScript_OfferHonedge
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
	goto MathieuHouse_2_EventScript_GuyFarewell
	end

MathieuHouse_2_EventScript_BagFullForDuskStone::
	msgbox MathieuHouse_2_Text_BagFullDuskStone, MSGBOX_DEFAULT
	goto MathieuHouse_2_EventScript_GuyFarewell
	end

MathieuHouse_2_Text_GuyIntro:
	.string "Hey, you're one of MATHIEU's friends,\n"
	.string "right?\p"
	.string "He asked me to hang onto a few of\n"
	.string "his favorite POKéMON and pass them\l"
	.string "along to trainers he trusts.$"

MathieuHouse_2_Text_OfferStarly:
	.string "First up, a STARLY.\p"
	.string "It's a scrappy little thing, but\n"
	.string "don't let that fool you.\p"
	.string "Would you like it?$"

MathieuHouse_2_Text_OfferHonedge:
	.string "Next, a HONEDGE.\p"
	.string "This one's a bit unusual, if you\n"
	.string "catch my drift.\p"
	.string "Would you like it?$"

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
