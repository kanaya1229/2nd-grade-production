// Pause.cpp

#include "Pause.h"
#include "DxLib.h"
#include "SceneManager.h"
#include <stdlib.h>
#include "UIButton.h"
#include "Init.h"
#include "ConfirmWindow.h"
#include "SaveData.h"

bool isPause = false;			// ポーズメニュー表示フラグ
bool showPauseMenu = false;		// 設定画面表示フラグ
bool escEdge;					// ESCキー入力判定

const int sliderX = 900;		// 音量スライダー位置
const int sliderW = 300;		// 音量スライダー幅
const int hitH = 30;			// スライダー判定範囲

bool dragMaster = false;		// マスター音量ドラッグ中
bool dragBGM = false;			// BGM音量ドラッグ中
bool dragSE = false;			// SE音量ドラッグ中

int masterVolume = 255;			// マスター音量
int bgmVolume = 255;			// BGM音量
int seVolume = 255;				// SE音量
// 設定画面の状態
SettingsMode settingsMode = SETTINGS_MAIN;

// ポーズ画面用ボタン
Button closeButton(600, 650, 320, 60);
Button ExitButton(600, 730, 320, 60);
Button controlButton(1020, 730, 320, 60);
Button resetButton(1020, 650, 320, 60);
Button backButton(1020, 730, 320, 60);

// ゲームを保存して終了できない時（タイトル、セーブ、ステータス、名前作成画面）
bool CanReturnTitle()
{
	return currentScene != SCENE_TITLE &&
		currentScene != SCENE_SAVESELECT &&
		currentScene != SCENE_STATUS &&
		currentScene != SCENE_NAME;
}
// 設定画面のアップデート
void UpdateSettings()
{

	int mx, my;
	GetMousePoint(&mx, &my);

	bool mouse =
		(GetMouseInput() & MOUSE_INPUT_LEFT);

	if (showConfirm) {
		return;
	}

	if (mouse)
	{
		if (!dragMaster &&
			!dragBGM &&
			!dragSE)
		{
			// MASTER
			if (mx >= sliderX &&
				mx <= sliderX + sliderW &&
				my >= 360 - hitH &&
				my <= 360 + hitH)
			{
				dragMaster = true;
			}

			// BGM
			else if (mx >= sliderX &&
				mx <= sliderX + sliderW &&
				my >= 440 - hitH &&
				my <= 440 + hitH)
			{
				dragBGM = true;
			}

			// SE
			else if (mx >= sliderX &&
				mx <= sliderX + sliderW &&
				my >= 520 - hitH &&
				my <= 520 + hitH)
			{
				dragSE = true;
			}
		}
	}
	else
	{
		dragMaster = false;
		dragBGM = false;
		dragSE = false;
	}

	if (dragMaster)
	{
		masterVolume =
			(mx - sliderX) * 255 / sliderW;

		masterVolume =
			max(0, min(255, masterVolume));
	}

	if (dragBGM)
	{
		bgmVolume =
			(mx - sliderX) * 255 / sliderW;

		bgmVolume =
			max(0, min(255, bgmVolume));
	}

	if (dragSE)
	{
		seVolume =
			(mx - sliderX) * 255 / sliderW;

		seVolume =
			max(0, min(255, seVolume));
	}


	// MAIN
	if (settingsMode == SETTINGS_MAIN)
	{

		if (closeButton.IsClicked() || escEdge)
		{
			showPauseMenu = false;
			isPause = false;

			SaveSettings();
		}

		if (ExitButton.IsClicked() && CanReturnTitle())
		{
			showConfirm = true;
			confirmType = CONFIRM_TITLE;
		}

		if (controlButton.IsClicked())
		{
			settingsMode =
				SETTINGS_CONTROL;
		}

		if (resetButton.IsClicked())
		{
			masterVolume = 255;
			bgmVolume = 255;
			seVolume = 255;
		}
	}

	// CONTROL

	else if (settingsMode == SETTINGS_CONTROL)
	{
		if (backButton.IsClicked() || IsKeyPressedOnce(KEY_INPUT_ESCAPE))
		{
			settingsMode =
				SETTINGS_MAIN;
		}
	}
}
// 設定画面の描画
void DrawSettings()
{
	DrawBox(
		500,
		200,
		1420,
		950,
		GetColor(0, 0, 0),
		TRUE);

	DrawBox(
		500,
		200,
		1420,
		950,
		GetColor(255, 255, 255),
		FALSE);

	// タイトル
	DrawString(
		700,
		250,
		"SETTINGS",
		GetColor(255, 255, 255));

	// メイン設定
	if (settingsMode == SETTINGS_MAIN)
	{
		// MASTER
		DrawFormatString(
			700,
			340,
			GetColor(255, 255, 255),
			"マスター : %d",
			masterVolume);

		DrawBox(
			900,
			350,
			1200,
			370,
			GetColor(80, 80, 80),
			TRUE);

		DrawBox(
			sliderX,
			350,
			sliderX + masterVolume * sliderW / 256,
			370,
			GetColor(255, 255, 255),
			TRUE);

		DrawCircle(
			sliderX + masterVolume * sliderW / 256,
			360,
			12,
			GetColor(255, 255, 255),
			TRUE);

		// BGM
		DrawFormatString(
			700,
			420,
			GetColor(255, 255, 255),
			"BGM : %d",
			bgmVolume);

		DrawBox(
			900,
			430,
			1200,
			450,
			GetColor(80, 80, 80),
			TRUE);

		DrawBox(
			sliderX,
			430,
			sliderX + bgmVolume * sliderW / 256,
			450,
			GetColor(255, 255, 255),
			TRUE);

		DrawCircle(
			sliderX + bgmVolume * sliderW / 256,
			440,
			12,
			GetColor(255, 255, 255),
			TRUE);

		// SE
		DrawFormatString(
			700,
			500,
			GetColor(255, 255, 255),
			"SE : %d",
			seVolume);

		DrawBox(
			900,
			510,
			1200,
			530,
			GetColor(80, 80, 80),
			TRUE);

		DrawBox(
			sliderX,
			510,
			sliderX + seVolume * sliderW / 256,
			530,
			GetColor(255, 255, 255),
			TRUE);

		DrawCircle(
			sliderX + seVolume * sliderW / 256,
			520,
			12,
			GetColor(255, 255, 255),
			TRUE);

		// ボタン
		closeButton.Draw(showConfirm);
		ExitButton.Draw(showConfirm);
		controlButton.Draw(showConfirm);
		resetButton.Draw(showConfirm);

		DrawString(
			closeButton.x + 110,
			closeButton.y + 20,
			"ゲームに戻る",
			GetColor(255, 255, 255));

		DrawString(
			ExitButton.x + 70,
			ExitButton.y + 20,
			"ゲームを保存して終了",
			GetColor(255, 255, 255));

		DrawString(
			controlButton.x + 110,
			controlButton.y + 20,
			"操作設定確認",
			GetColor(255, 255, 255));

		DrawString(
			resetButton.x + 110,
			resetButton.y + 20,
			"音量リセット",
			GetColor(255, 255, 255));
	}

	// 操作設定
	else if (settingsMode == SETTINGS_CONTROL)
	{
		DrawString(
			700,
			350,
			"マウス左クリック：　基本操作（ ボタンや選択 ）",
			GetColor(255, 255, 255));

		DrawString(
			700,
			430,
			"TAB：　アイテム欄や情報まとめ",
			GetColor(255, 255, 255));

		DrawString(
			700,
			510,
			"注意：　このゲームはクリックした際にダイスロールが行われます。",
			GetColor(255, 255, 255));

		backButton.Draw(false);

		DrawString(
			backButton.x + 90,
			backButton.y + 20,
			"一つ戻る",
			GetColor(255, 255, 255));
	}
}
// 設定したデータの保存
void SaveSettings()
{
	FILE* fp;

	fopen_s(
		&fp,
		"settings.dat",
		"wb");

	if (!fp)
	{
		return;
	}

	fwrite(
		&masterVolume,
		sizeof(int),
		1,
		fp);

	fwrite(
		&bgmVolume,
		sizeof(int),
		1,
		fp);

	fwrite(
		&seVolume,
		sizeof(int),
		1,
		fp);

	fclose(fp);
}
// ゲーム開始時にデータをロード
void LoadSettings()
{
	FILE* fp;

	fopen_s(
		&fp,
		"settings.dat",
		"rb");

	if (!fp)
	{
		masterVolume = 255;
		bgmVolume = 255;
		seVolume = 255;

		return;
	}

	fread(
		&masterVolume,
		sizeof(int),
		1,
		fp);

	fread(
		&bgmVolume,
		sizeof(int),
		1,
		fp);

	fread(
		&seVolume,
		sizeof(int),
		1,
		fp);

	fclose(fp);
}