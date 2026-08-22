PetalburgDepths_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PetalburgDepths_B2F_OnLoad
	.byte 0

PetalburgDepths_B2F_OnLoad:
	call_if_set FLAG_DEFEATED_PETALBURG_DEPTHS_B2F, PetalburgDepths_B2F_EventScript_OpenGate
	end

PetalburgDepths_B2F_EventScript_OpenGate::
	setmetatile 6, 1, METATILE_EliteFour_OpenDoor_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoor_Opening, FALSE
	special DrawWholeMapView
	return

PetalburgDepths_B2F_EventScript_Boss::
	trainerbattle_single TRAINER_PETALBURG_DEPTHS_BOSS2, PetalburgDepths_B2F_Text_BossIntro, PetalburgDepths_B2F_Text_BossDefeat, PetalburgDepths_B2F_EventScript_BossWon
	msgbox PetalburgDepths_B2F_Text_BossPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgDepths_B2F_EventScript_BossWon::
	setflag FLAG_DEFEATED_PETALBURG_DEPTHS_B2F
	call PetalburgDepths_B2F_EventScript_OpenGate
	msgbox PetalburgDepths_B2F_Text_BossPostBattle, MSGBOX_AUTOCLOSE
	release
	end

PetalburgDepths_B2F_Text_BossIntro:
	.string "KESTREL: You've got a good pace\n"
	.string "on you. Let's see your footwork\l"
	.string "against mine!$"

PetalburgDepths_B2F_Text_BossDefeat:
	.string "KESTREL: Ngh… out of gas already.\n"
	.string "Not bad!$"

PetalburgDepths_B2F_Text_BossPostBattle:
	.string "KESTREL: Go on, the tunnel splits\n"
	.string "open behind me. It gets meaner\l"
	.string "from here.$"

PetalburgDepths_B2F_EventScript_WildPatch::
	lock
	faceplayer
	msgbox PetalburgDepths_B2F_Text_WildPatch, MSGBOX_DEFAULT
	setwildbattle SPECIES_GLIGAR, 23
	waitse
	playmoncry SPECIES_GLIGAR, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	release
	end

PetalburgDepths_B2F_Text_WildPatch:
	.string "Something rustles in the debris\n"
	.string "here…$"
