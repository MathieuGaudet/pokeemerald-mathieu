PetalburgDepths_B4F_MapScripts::
	.byte 0

PetalburgDepths_B4F_EventScript_Boss::
	trainerbattle_single TRAINER_PETALBURG_DEPTHS_BOSS4, PetalburgDepths_B4F_Text_BossIntro, PetalburgDepths_B4F_Text_BossDefeat, PetalburgDepths_B4F_EventScript_BossWon
	msgbox PetalburgDepths_B4F_Text_BossPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgDepths_B4F_EventScript_BossWon::
	setflag FLAG_DEFEATED_PETALBURG_DEPTHS_B4F
	removeobject VAR_LAST_TALKED
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
