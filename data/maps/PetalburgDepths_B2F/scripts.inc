PetalburgDepths_B2F_MapScripts::
	.byte 0

PetalburgDepths_B2F_EventScript_Boss::
	trainerbattle_single TRAINER_PETALBURG_DEPTHS_BOSS2, PetalburgDepths_B2F_Text_BossIntro, PetalburgDepths_B2F_Text_BossDefeat, PetalburgDepths_B2F_EventScript_BossWon
	msgbox PetalburgDepths_B2F_Text_BossPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgDepths_B2F_EventScript_BossWon::
	setflag FLAG_DEFEATED_PETALBURG_DEPTHS_B2F
	removeobject VAR_LAST_TALKED
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
