PetalburgDepths_B1F_MapScripts::
	.byte 0

PetalburgDepths_B1F_EventScript_Boss::
	trainerbattle_single TRAINER_PETALBURG_DEPTHS_BOSS1, PetalburgDepths_B1F_Text_BossIntro, PetalburgDepths_B1F_Text_BossDefeat, PetalburgDepths_B1F_EventScript_BossWon
	msgbox PetalburgDepths_B1F_Text_BossPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgDepths_B1F_EventScript_BossWon::
	setflag FLAG_DEFEATED_PETALBURG_DEPTHS_B1F
	removeobject VAR_LAST_TALKED
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
