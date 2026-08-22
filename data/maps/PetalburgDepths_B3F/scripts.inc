PetalburgDepths_B3F_MapScripts::
	.byte 0

PetalburgDepths_B3F_EventScript_Boss::
	trainerbattle_single TRAINER_PETALBURG_DEPTHS_BOSS3, PetalburgDepths_B3F_Text_BossIntro, PetalburgDepths_B3F_Text_BossDefeat, PetalburgDepths_B3F_EventScript_BossWon
	msgbox PetalburgDepths_B3F_Text_BossPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgDepths_B3F_EventScript_BossWon::
	setflag FLAG_DEFEATED_PETALBURG_DEPTHS_B3F
	removeobject VAR_LAST_TALKED
	msgbox PetalburgDepths_B3F_Text_BossPostBattle, MSGBOX_AUTOCLOSE
	release
	end

PetalburgDepths_B3F_Text_BossIntro:
	.string "MORWENNA: Mm… fresh company.\n"
	.string "It gets so quiet down here.\p"
	.string "Let's not be quiet anymore.$"

PetalburgDepths_B3F_Text_BossDefeat:
	.string "MORWENNA: Heh… the shadows favor\n"
	.string "you today.$"

PetalburgDepths_B3F_Text_BossPostBattle:
	.string "MORWENNA: Go on ahead. Whatever\n"
	.string "you find in the dark past here…\l"
	.string "it's yours.$"
