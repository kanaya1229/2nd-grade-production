#include "SaveData.h"
#include "Init.h"
#include "UIButton.h"
#include "SceneManager.h"
#include "DxLib.h"
#include <stdio.h>
#include "ConfirmWindow.h"
#include "Pause.h"

// ボタン
Button slots[4] =
{
	Button(400, 180, 700, 90),
	Button(400, 300, 700, 90),
	Button(400, 420, 700, 90),
	Button(400, 540, 700, 90)
};

Button deleteData[4] = 
{

	Button(1280, 180, 260, 90),
	Button(1280, 300, 260, 90),
	Button(1280, 420, 260, 90),
	Button(1280, 540, 260, 90),
};

Button backTitle(30, 30, 260, 80);

PlayerData player;
PlayerData saveSlots[4];

int currentSlot = 1;
// 特定のスロットにゲームを保存
void SaveGame(int slot)
{
	char filename[64];
	sprintf_s(filename, sizeof(filename), "save%d.dat", slot);

	FILE* fp;
	fopen_s(&fp, filename, "wb");
	if (!fp) return;

	fwrite(&player, sizeof(PlayerData), 1, fp);

	fclose(fp);

	// ←ここ重要
	saveSlots[slot - 1] = player;
}
// 特定のスロットにゲームをロード
bool LoadGame(int slot)
{
	char filename[64];
	sprintf_s(filename, sizeof(filename), "save%d.dat", slot);

	FILE* fp;
	fopen_s(&fp, filename, "rb");
	if (!fp) return false;

	fread(&player, sizeof(PlayerData), 1, fp);

	fclose(fp);
	return true;
}
// もしデータがなかったら初期化
void LoadAllSaveData()
{
	for (int i = 0; i < 4; i++)
	{
		char filename[64];
		sprintf_s(filename, sizeof(filename),
			"save%d.dat", i + 1);

		FILE* fp;
		fopen_s(&fp, filename, "rb");

		if (fp)
		{
			fread(&saveSlots[i],
				sizeof(PlayerData), 1, fp);

			fclose(fp);
		}
		else
		{
			saveSlots[i].stage = 0;
			saveSlots[i].hp = 0;

		}
	}
}
// セーブデータ画面のアップデート
void UpdateSaveSelectScene()
{
	if (confirmType) {
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		if (slots[i].IsClicked())
		{
			currentSlot = i + 1;

			// NEW GAME
			if (saveMode == MODE_NEW_GAME)
			{
				if (saveSlots[i].stage == 0)
				{
					player = CreateDefaultPlayer();

					memset(player.name, 0,
						sizeof(player.name));

					statusMode = STATUS_EDIT;
					currentScene = SCENE_STATUS;
				}
			}

			// CONTINUE
			else if (saveMode == MODE_LOAD_GAME)
			{
				if (saveSlots[i].stage != 0)
				{
					LoadGame(i + 1);

					if (saveSlots[i].storyCleared)
					{
						currentScene = SCENE_GAMEIN;
					}
					else
					{
						currentScene = SCENE_STARTGAME;
					}
				}
			}
		}

		if (deleteData[i].IsClicked() &&
			saveSlots[i].stage != 0)
		{
			showConfirm = true;
			confirmType = CONFIRM_DELETE;
			targetSlot = i + 1;
		}
	}

	if (backTitle.IsClicked())
	{
		currentScene = SCENE_TITLE;
	}
}
// セーブデータ画面の描画
void DrawSaveScene()
{

	DrawString(450, 100, _T("Save Data"), GetColor(255, 255, 255));

	PlayerData temp;
	char buf[128];

	backTitle.Draw(showConfirm || isPause);

	for (int i = 1; i <= 4; i++)
	{
		slots[i - 1].Draw(showConfirm || isPause);
		deleteData[i - 1].Draw(showConfirm || isPause);

		int baseY = 190 + (i - 1) * 120;

		temp = saveSlots[i - 1];

		if (temp.stage != 0)
		{
			int x = 420;
			int y0 = baseY;
			int line = 28;


			DrawString(
				x,
				y0,
				temp.name,
				GetColor(0, 255, 0)
			);

			// 2行目
			DrawFormatString(
				x,
				y0 + line,
				GetColor(0, 255, 0),
				"HP:%d STR:%d CON:%d POW:%d DEX:%d APP:%d SIZ:%d INT:%d EDU:%d",
				temp.hp,
				temp.str,
				temp.con,
				temp.pow,
				temp.dex,
				temp.app,
				temp.siz,
				temp.intel,
				temp.edu
			);

			// 3行目（ここだけ少し離す）
			DrawFormatString(
				x,
				y0 + line * 2,  // ←ここが「余白」
				GetColor(0, 255, 0),
				"TEC:%d KNW:%d INS:%d",
				temp.tec,
				temp.knw,
				temp.insight
			);
		}
		else
		{
			DrawString(420, baseY,
				"NEW GAME",
				GetColor(100, 100, 100));
		}

		DrawString(
			deleteData[i - 1].x + 30,
			deleteData[i - 1].y + 30,
			"DELETE",
			GetColor(255, 255, 255));
	}

	DrawString(
		100,
		60,
		"GO TITLE",
		GetColor(255, 255, 255));

}
// データを消去
void DeleteSaveData(int slot)
{
	char filename[64];

	sprintf_s(
		filename,
		sizeof(filename),
		"save%d.dat",
		slot);

	remove(filename);

	// スロット初期化
	saveSlots[slot - 1] =
		CreateDefaultPlayer();

	// 未使用扱い
	saveSlots[slot - 1].stage = 0;

	// 現在プレイヤーも初期化
	player = CreateDefaultPlayer();

	LoadAllSaveData();
}