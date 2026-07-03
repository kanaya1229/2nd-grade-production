#include <string>
#include "Init.h"
#include "SaveData.h"
#include "BattleScene.h"
#include "ExploreScene.h"
#include "Pause.h"
#include "EndingScene.h"
#include "SceneManager.h"
#include "BGM.h"

Button NextButton(
	1550, 880,
	250, 100);

Button battleButton1(
	1250, 760,
	550, 60);

Button battleButton2(
	1250, 840,
	550, 60);

Button battleButton3(
	1250, 920,
	550, 60);

Button battleButton4(
	1250, 1000,
	550, 60);

// 最終戦用フォント
int BattleFont;

char B_message[2048] = "";			// メッセージ表示用文字列
int B_LastDice;						// 直前のダイス結果
int finalIntroState = FINAL_INTRO_1;// 導入イベントの進行状態

// 背景画像
int LastRoomImage;
int EnemyImage;
int LastLabImage;
int LastHallImage;

FinalBattleState finalBattleState;	// 現在の戦闘状態
FinalBattleState enemyRoom;			// 敵を表示する部屋
FinalBattleState previousRoom;		// 直前にいた部屋

bool checkedHall;					// 廊下確認フラグ
bool checkedLab;					// 研究室確認フラグ
bool endingStarted = false;			// エンディング開始フラグ

int shakeTimer = 0;					// 画面揺れ演出タイマー

// 最終戦用の画像やフォントを読み込む
void InItFinalBattle() {

	BattleFont =
		CreateFontToHandle(
			"Yu Gothic UI",
			40,
			3);

	LastRoomImage = LoadGraph("Image\\Lastroom.png");
	EnemyImage = LoadGraph("Image\\Enemy.png");
	LastLabImage = LoadGraph("Image\\finalLab.png");
	LastHallImage = LoadGraph("Image\\finalHall.png");
}
// 1D100による判定を行う
bool SkillCheck100(int skill)
{
	B_LastDice = RollDice(100);

	return B_LastDice <= skill;
}
// 敵の攻撃処理
void EnemyAttack()
{
	int damage;

	if (SkillCheck100(player.str * 4))
	{
		strcpy_s(B_message,
			"異形が襲い掛かってきた！\n\n"
			"何とか振り払った！");
	}
	else
	{
		damage = GetRand(3) + 1;

		player.hp -= damage;

		shakeTimer = 20; // 20フレーム揺れる

		playerFace = FACE_DAMAGE;

		PlaySoundMem(
			seDamage,
			DX_PLAYTYPE_BACK);

		sprintf_s(
			B_message,
			"異形が襲い掛かってきた！\n\n"
			"%d ダメージ！",
			damage);
	}

	if (player.hp <= 0)
	{
		player.hp = 0;
		finalBattleState = END3;
		return;
	}

	// 元の部屋へ戻す
	finalBattleState = previousRoom;
}
// 最終戦の初期設定を行う
void StartFinalBattle()
{
	endingStarted = false;

	finalIntroState = FINAL_INTRO_1;
	finalBattleState = FINALROOM;

	checkedHall = false;
	checkedLab = false;


	if (player.hasMask) {
		strcpy_s(B_message,
			"炎の奥に白く輝く異形がいる。\n\n"
			"何をする？");
	}
	else {

		playerFace = FACE_DAMAGE;

		strcpy_s(B_message,
			"呼吸が出来ない。\n"
			"視界が暗く閉ざされていく。");

	}

}
// 敵ターンへ移行する
void NextRound()
{
	finalBattleState = ENEMY_MOVE;
}
// 最終部屋での行動選択を処理する
void UpdateFinalRoom()
{
	if (battleButton1.IsClicked())
	{
		strcpy_s(B_message,
			"異形は炎を指差している。\n\n"
			"『なおして』");
		
		playerFace = FACE_THINK;

		previousRoom = FINALROOM;
		NextRound();
	}

	if (battleButton2.IsClicked())
	{
		strcpy_s(B_message,
			"廊下へ向かった。");

		playerFace = FACE_NORMAL;
		finalBattleState = HALL;
		previousRoom = HALL;
		NextRound();
	}

	if (battleButton3.IsClicked())
	{
		if (SkillCheck(player.dex))
		{
			strcpy_s(B_message,
				"出口へ駆け抜けた！");
			playerFace = FACE_DAMAGE;
			finalBattleState = END2;
		}
		else
		{
			strcpy_s(B_message,
				"炎に阻まれた！");
			playerFace = FACE_DAMAGE;
			previousRoom = FINALROOM;
			NextRound();
		}
	}
}
// 廊下での行動選択を処理する
void UpdateHall()
{
	if (!checkedHall)
	{
		checkedHall = true;

		return;
	}

	if (battleButton1.IsClicked())
	{
		if (SkillCheck(player.dex * 4))
		{
			strcpy_s(B_message,
				"消火器を噴射した！");
			playerFace = FACE_NORMAL;
			finalBattleState = END1;
		}
		else
		{
			strcpy_s(B_message,
				"うまく扱えなかった！");
			playerFace = FACE_DAMAGE;
			previousRoom = HALL;
			NextRound();
		}
	}

	if (battleButton2.IsClicked())
	{
		strcpy_s(B_message,
			"研究室へ向かった。");
		playerFace = FACE_NORMAL;
		previousRoom = LAB;
		NextRound();
	}

	if (battleButton3.IsClicked())
	{
		strcpy_s(B_message,
			"最終部屋へ戻った。");
		playerFace = FACE_NORMAL;
		previousRoom = FINALROOM;
		NextRound();
	}
}
// 研究室での行動選択を処理する
void UpdateLab()
{
	if (!checkedLab)
	{
		checkedLab = true;

		return;
	}

	if (battleButton1.IsClicked())
	{
		if (SkillCheck(player.dex * 4))
		{
			strcpy_s(B_message,
				"ホースを起動した！");
			playerFace = FACE_NORMAL;
			finalBattleState = END1A;
		}
		else
		{
			strcpy_s(B_message,
				"ホースをうまく扱えない！");
			playerFace = FACE_DAMAGE;
			previousRoom = LAB;
			NextRound();
		}
	}

	if (battleButton2.IsClicked())
	{
		strcpy_s(B_message,
			"廊下へ戻った。");
		playerFace = FACE_NORMAL;
		previousRoom = HALL;
		NextRound();
	}
}
// 最終戦全体の進行を管理する
void Update_FinalBattle()
{

	UpdatePlayerFace();

	if (shakeTimer > 0)
	{
		shakeTimer--;
	}

	static bool n = false;

	if (!player.hasMask && !n) {

		finalIntroState = FINAL_BATTLE;

		finalBattleState = END3;

		n = true;
	}

	if (!isPause) {

		switch (finalIntroState)
		{
		case FINAL_INTRO_1:

			playerFace = FACE_DAMAGE;

			strcpy_s(B_message,
				"この部屋だけ以上に熱い.....!\n"
				"こいつはなんだ？！？！\n"
				"こんなのただの化け物だ。");

			if (NextButton.IsClicked())
			{
				strcpy_s(B_message,
					"廊下の奥を見る。\n\n"
					"開いた扉から炎が溢れている。\n\n"
					"その奥に白く輝く何かがいた。");

				finalIntroState = FINAL_INTRO_2;
			}
			break;

		case FINAL_INTRO_2:

			if (NextButton.IsClicked())
			{
				int loss;

				if (SkillCheck100(player.pow * 4))
				{

					playerFace = FACE_THINK;

					sprintf_s(B_message,
						"1D100 -> %d \n"
						"成功！(精神力 × ４) \n"
						"何とか正気を保てている。\n"
						"その存在は人の形をしているようで\n"
						"そうではなかった。", B_LastDice);
				}
				else
				{
					playerFace = FACE_DAMAGE;

					loss = GetRand(2) + 1;

					player.hp -= loss;

					PlaySoundMem(
						sePoison,
						DX_PLAYTYPE_BACK);

					sprintf_s(B_message,
						"1D100 -> %d \n"
						"失敗.....  (精神力 × ４) \n"
						"HPが %d 減った....."
						"白く輝く異形が蠢いている。",
						B_LastDice, loss);
				}

				finalIntroState = FINAL_INTRO_3;
			}
			break;

		case FINAL_INTRO_3:

			if (NextButton.IsClicked())
			{
				if (SkillCheck100(player.intel * 4))
				{
					playerFace = FACE_THINK;

					sprintf_s(B_message,
						"1D100 -> %d \n"
						"成功！　(知性 × ４)\n"
						"異形は炎を指差した。\n"
						"『なおして』\n"
						"そう言ったように聞こえた。",
						B_LastDice);
				}
				else
				{
					playerFace = FACE_DAMAGE;

					sprintf_s(B_message,
						"1D100 -> %d \n"
						"失敗.....　(知性 × ４)\n"
						"異形は何かを発している。\n"
						"しかし聞き取れない。",
						B_LastDice);
				}

				finalIntroState = FINAL_INTRO_4;
			}
			break;

		case FINAL_INTRO_4:

			if (NextButton.IsClicked())
			{
				StartFinalBattle();


				if (player.hasMask) {
					strcpy_s(B_message,
						"火は燃え広がっている。\n\n"
						"どうする？！？");
				}

				finalIntroState = FINAL_BATTLE;

				playerFace = FACE_NORMAL;
			}

			break;
		case FINAL_BATTLE:

			switch (finalBattleState)
			{
			case FINALROOM:

				enemyRoom = finalBattleState;

				UpdateFinalRoom();

				break;

			case HALL:

				enemyRoom = finalBattleState;

				UpdateHall();

				break;

			case LAB:

				enemyRoom = finalBattleState;

				UpdateLab();

				break;

			case ENEMY_MOVE:

				
				if (NextButton.IsClicked())
				{
					EnemyAttack();
				}


				break;

			case END1:
				NextButton.Draw(isPause);

				DrawString(
					1600,
					920,
					"エンディングへ",
					GetColor(255, 255, 255));

				if (NextButton.IsClicked())
				{
					if (!endingStarted)
					{
						PlayBGM(bgmEndingHappy);
						StartEnding(ENDING_1);
						currentScene = SCENE_ENDING;
						endingStarted = true;
					}
				}
				break;

			case END1A:

				NextButton.Draw(isPause);

				DrawString(
					1600,
					920,
					"エンディングへ",
					GetColor(255, 255, 255));

				if (NextButton.IsClicked())
				{
					if (!endingStarted)
					{
						PlayBGM(bgmEndingHappy);
						StartEnding(ENDING_1A);
						currentScene = SCENE_ENDING;
						endingStarted = true;
					}
				}
				break;
			case END2:

				NextButton.Draw(isPause);

				DrawString(
					1600,
					920,
					"エンディングへ",
					GetColor(255, 255, 255));

				if (NextButton.IsClicked())
				{
					if (!endingStarted)
					{
						PlayBGM(bgmEndingBad);
						StartEnding(ENDING_2);
						currentScene = SCENE_ENDING;
						endingStarted = true;
					}
				}
				break;

			case END3:

				NextButton.Draw(isPause);

				DrawString(
					1600,
					920,
					"エンディングへ",
					GetColor(255, 255, 255));

				if (NextButton.IsClicked())
				{
					if (!endingStarted)
					{

						PlayBGM(bgmEndingBad);
						StartEnding(ENDING_3);
						currentScene = SCENE_ENDING;
						endingStarted = true;
					}
				}
				break;
			}
		}
	}
}
// 最終戦画面を描画する
void Draw_FinalBattle()
{
	int shakeX = 0;
	int shakeY = 0;

	if (shakeTimer > 0)
	{
		shakeX = GetRand(12) - 6;
		shakeY = GetRand(12) - 6;
	}


	if (finalBattleState == ENEMY_MOVE)
	{
		switch (previousRoom)
		{
		case FINALROOM:
			DrawExtendGraph(
				shakeX,
				shakeY,
				1920 + shakeX,
				1080 + shakeY,
				LastRoomImage,
				TRUE);
			break;

		case HALL:
			DrawExtendGraph(
				shakeX,
				shakeY,
				1920 + shakeX,
				1080 + shakeY,
				LastHallImage,
				TRUE);
			break;

		case LAB:
			DrawExtendGraph(
				shakeX,
				shakeY,
				1920 + shakeX,
				1080 + shakeY,
				LastLabImage,
				TRUE);
			break;
		}
	}
	else
	{
		switch (finalBattleState)
		{
		case FINALROOM:
			DrawExtendGraph(
				shakeX,
				shakeY,
				1920 + shakeX,
				1080 + shakeY,
				LastRoomImage,
				TRUE);
			break;

		case HALL:
			DrawExtendGraph(
				shakeX,
				shakeY,
				1920 + shakeX,
				1080 + shakeY,
				LastHallImage,
				TRUE);
			break;

		case LAB:
			DrawExtendGraph(
				shakeX,
				shakeY,
				1920 + shakeX,
				1080 + shakeY,
				LastLabImage,
				TRUE);
			break;
		}
	}

	DrawPlayer();

	if (enemyRoom == finalBattleState)
	{
		DrawExtendGraph(
			900, 100,
			1800, 950,
			EnemyImage,
			TRUE);
	}

	// メッセージ枠
	DrawBox(40, 760, 1180, 1040,
		GetColor(20, 20, 20), TRUE);

	DrawBox(40, 760, 1180, 1040,
		GetColor(255, 255, 255), FALSE);

	DrawStringToHandle(
		70,
		790,
		B_message,
		GetColor(255, 255, 255),
		BattleFont);

	// 次へ
	if (finalIntroState == FINAL_BATTLE)
	{
		DrawBox(
			20,
			20,
			130,
			90,
			GetColor(0, 0, 0),
			TRUE);

		DrawBox(
			20,
			20,
			130,
			90,
			GetColor(255, 255, 255),
			FALSE);

		DrawFormatString(
			40,
			35,
			GetColor(255, 255, 255),
			"HP");

		DrawFormatString(
			70,
			35,
			GetColor(255, 255, 255),
			"%d",
			player.hp);


		switch (finalBattleState)
		{
		case FINALROOM:

			battleButton1.Draw(isPause);
			battleButton2.Draw(isPause);
			battleButton3.Draw(isPause);

			DrawString(
				1450,
				780,
				"観察",
				GetColor(255, 255, 255));

			DrawString(
				1450,
				860,
				"廊下へ",
				GetColor(255, 255, 255));

			DrawString(
				1450,
				940,
				"出口へ",
				GetColor(255, 255, 255));

			break;

		case HALL:


			battleButton1.Draw(isPause);

			DrawString(
				1400,
				780,
				"消火器使用",
				GetColor(255, 255, 255));


			battleButton2.Draw(isPause);

			DrawString(
				1450,
				860,
				"研究室へ",
				GetColor(255, 255, 255));

			battleButton3.Draw(isPause);

			DrawString(
				1450,
				940,
				"最終部屋に戻る",
				GetColor(255, 255, 255));

			break;

		case LAB:

			battleButton1.Draw(isPause);

			DrawString(
				1400,
				780,
				"ホース使用",
				GetColor(255, 255, 255));

			battleButton2.Draw(isPause);

			DrawString(
				1450,
				860,
				"廊下へ",
				GetColor(255, 255, 255));

			break;

		case ENEMY_MOVE:

			NextButton.Draw(isPause);

			break;
		}
	}
	else {
		NextButton.Draw(isPause);

		DrawString(
			1650,
			920,
			"次へ",
			GetColor(255, 255, 255));
	}
}
