#pragma once


enum FinalBattleState
{
	FINALROOM,
	HALL,
	LAB,

	ENEMY_MOVE,

	END1,		// è¡âŒäÌ
	END1A,		// ÉzÅ[ÉX
	END2,		// ì¶ëñ
	END3		// éÄñS
};

enum FinalRoomState
{
    FINAL_STORY,
    FINAL_SELECT
};

enum FinalIntroState
{
	FINAL_INTRO_1,
	FINAL_INTRO_2,
	FINAL_INTRO_3,
	FINAL_INTRO_4,
	FINAL_BATTLE
};

extern int finalIntroState;
extern FinalBattleState finalBattleState;

void InItFinalBattle();
void StartFinalBattle();
void Update_FinalBattle();
void Draw_FinalBattle();