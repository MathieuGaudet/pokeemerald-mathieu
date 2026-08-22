PetalburgDepths_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PetalburgDepths_B1F_OnLoad
	.byte 0

PetalburgDepths_B1F_OnLoad:
	call_if_set FLAG_DEFEATED_PETALBURG_DEPTHS_B1F, PetalburgDepths_B1F_EventScript_OpenGate
	end

PetalburgDepths_B1F_EventScript_OpenGate::
	setmetatile 6, 1, METATILE_EliteFour_OpenDoor_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoor_Opening, FALSE
	special DrawWholeMapView
	return

PetalburgDepths_B1F_EventScript_Boss::
	trainerbattle_single TRAINER_PETALBURG_DEPTHS_BOSS1, PetalburgDepths_B1F_Text_BossIntro, PetalburgDepths_B1F_Text_BossDefeat, PetalburgDepths_B1F_EventScript_BossWon
	msgbox PetalburgDepths_B1F_Text_BossPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgDepths_B1F_EventScript_BossWon::
	setflag FLAG_DEFEATED_PETALBURG_DEPTHS_B1F
	call PetalburgDepths_B1F_EventScript_OpenGate
	msgbox PetalburgDepths_B1F_Text_BossPostBattle, MSGBOX_AUTOCLOSE
	release
	end

PetalburgDepths_B1F_Text_BossIntro:
	.string "BOREK: Not many trainers make it\n"
	.string "this deep on their first try.\p"
	.string "Let's see if you can handle a real\n"
	.string "cave-in!$"

PetalburgDepths_B1F_Text_BossDefeat:
	.string "BOREK: Progh! The rocks… they didn't\n"
	.string "hold…$"

PetalburgDepths_B1F_Text_BossPostBattle:
	.string "BOREK: The path deeper into the\n"
	.string "DEPTHS is open now. Watch your\l"
	.string "step down there.$"

PetalburgDepths_B1F_EventScript_WildPatch::
	lock
	faceplayer
	msgbox PetalburgDepths_B1F_Text_WildPatch, MSGBOX_DEFAULT
	setwildbattle SPECIES_LARVITAR, 18
	waitse
	playmoncry SPECIES_LARVITAR, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	release
	end

PetalburgDepths_B1F_Text_WildPatch:
	.string "Something rustles in the debris\n"
	.string "here…$"
