PetalburgDepths_B5F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PetalburgDepths_B5F_OnLoad
	.byte 0

PetalburgDepths_B5F_OnLoad:
	call_if_set FLAG_DEFEATED_PETALBURG_DEPTHS_B5F, PetalburgDepths_B5F_EventScript_OpenGate
	end

PetalburgDepths_B5F_EventScript_OpenGate::
	setmetatile 6, 1, METATILE_EliteFour_OpenDoor_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoor_Opening, FALSE
	special DrawWholeMapView
	return

PetalburgDepths_B5F_EventScript_Boss::
	trainerbattle_single TRAINER_PETALBURG_DEPTHS_BOSS5, PetalburgDepths_B5F_Text_BossIntro, PetalburgDepths_B5F_Text_BossDefeat, PetalburgDepths_B5F_EventScript_BossWon
	msgbox PetalburgDepths_B5F_Text_BossPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgDepths_B5F_EventScript_BossWon::
	setflag FLAG_DEFEATED_PETALBURG_DEPTHS_B5F
	call PetalburgDepths_B5F_EventScript_OpenGate
	msgbox PetalburgDepths_B5F_Text_BossPostBattle, MSGBOX_AUTOCLOSE
	release
	end

PetalburgDepths_B5F_Text_BossIntro:
	.string "ISOLDE: So. You made it all the way\n"
	.string "down to the bottom of the DEPTHS.\p"
	.string "I've watched this chamber for a\n"
	.string "long time, waiting for someone who\l"
	.string "could actually push me.\p"
	.string "Let's find out if that's you!$"

PetalburgDepths_B5F_Text_BossDefeat:
	.string "ISOLDE: …Finally. Someone who\n"
	.string "belongs down here as much as I do.$"

PetalburgDepths_B5F_Text_BossPostBattle:
	.string "ISOLDE: Take what's behind me. You\n"
	.string "earned every bit of it.\p"
	.string "Come back anytime you want another\n"
	.string "real battle.$"

PetalburgDepths_B5F_EventScript_WildPatch::
	lock
	faceplayer
	msgbox PetalburgDepths_B5F_Text_WildPatch, MSGBOX_DEFAULT
	setwildbattle SPECIES_GIBLE, 36
	waitse
	playmoncry SPECIES_GIBLE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	release
	end

PetalburgDepths_B5F_Text_WildPatch:
	.string "Something rustles in the debris\n"
	.string "here…$"
