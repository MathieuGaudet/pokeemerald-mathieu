PetalburgDepths_B5F_MapScripts::
	.byte 0

PetalburgDepths_B5F_EventScript_Boss::
	trainerbattle_single TRAINER_PETALBURG_DEPTHS_BOSS5, PetalburgDepths_B5F_Text_BossIntro, PetalburgDepths_B5F_Text_BossDefeat, PetalburgDepths_B5F_EventScript_BossWon
	msgbox PetalburgDepths_B5F_Text_BossPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgDepths_B5F_EventScript_BossWon::
	setflag FLAG_DEFEATED_PETALBURG_DEPTHS_B5F
	removeobject VAR_LAST_TALKED
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
