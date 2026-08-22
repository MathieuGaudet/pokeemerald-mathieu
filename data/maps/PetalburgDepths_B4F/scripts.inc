PetalburgDepths_B4F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PetalburgDepths_B4F_OnLoad
	.byte 0

PetalburgDepths_B4F_OnLoad:
	call_if_set FLAG_DEFEATED_PETALBURG_DEPTHS_B4F, PetalburgDepths_B4F_EventScript_OpenGate
	end

PetalburgDepths_B4F_EventScript_OpenGate::
	setmetatile 6, 1, METATILE_EliteFour_OpenDoor_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoor_Opening, FALSE
	special DrawWholeMapView
	return

PetalburgDepths_B4F_EventScript_Boss::
	trainerbattle_single TRAINER_PETALBURG_DEPTHS_BOSS4, PetalburgDepths_B4F_Text_BossIntro, PetalburgDepths_B4F_Text_BossDefeat, PetalburgDepths_B4F_EventScript_BossWon
	msgbox PetalburgDepths_B4F_Text_BossPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgDepths_B4F_EventScript_BossWon::
	setflag FLAG_DEFEATED_PETALBURG_DEPTHS_B4F
	call PetalburgDepths_B4F_EventScript_OpenGate
	msgbox PetalburgDepths_B4F_Text_BossPostBattle, MSGBOX_AUTOCLOSE
	release
	end

PetalburgDepths_B4F_Text_BossIntro:
	.string "THORVALD: This deep, the air itself\n"
	.string "feels old. My team can feel it too.\p"
	.string "Show me you belong down here!$"

PetalburgDepths_B4F_Text_BossDefeat:
	.string "THORVALD: Impressive. Even they\n"
	.string "felt that.$"

PetalburgDepths_B4F_Text_BossPostBattle:
	.string "THORVALD: One floor left. Whatever\n"
	.string "is guarding the bottom of this place…\l"
	.string "it's the real thing.$"

PetalburgDepths_B4F_EventScript_WildPatch::
	lock
	faceplayer
	msgbox PetalburgDepths_B4F_Text_WildPatch, MSGBOX_DEFAULT
	setwildbattle SPECIES_DEINO, 32
	waitse
	playmoncry SPECIES_DEINO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	release
	end

PetalburgDepths_B4F_Text_WildPatch:
	.string "Something rustles in the debris\n"
	.string "here…$"
