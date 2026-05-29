#include "TitleScene.h"
#include "UIButton.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "Init.h"
#include "ConfirmWindow.h"
#include "Pause.h"

int titleImage;
int vignetteHandle;
int startButtonImage;
int continueButtonImage;
int exitButtonImage;

int masterSoundHandle;
int bgmSoundHandle;
int seSoundHandle;

Button startBtn(1350, 700, 400, 90);
Button continueBtn(1350, 810, 400, 90);
Button exitBtn(1350, 920, 400, 90);
// タイトルシーンの初期化
void InitTitleScene()
{

	startButtonImage = LoadGraph("Image\\Start.png");
	continueButtonImage = LoadGraph("Image\\continue.png");
	exitButtonImage = LoadGraph("Image\\exit.png");
	vignetteHandle = LoadGraph("Image\\R.png");
	titleImage = LoadGraph("Image\\Title.png");
}
// タイトルシーンのアップデート
void UpdateTitleScene()
{
	if (startBtn.IsClicked())
	{
		saveMode = MODE_NEW_GAME;
		currentScene = SCENE_SAVESELECT;
	}

	if (continueBtn.IsClicked())
	{
		saveMode = MODE_LOAD_GAME;
		currentScene = SCENE_SAVESELECT;
	}

	if (exitBtn.IsClicked())
	{
		showConfirm = true;
		confirmType = CONFIRM_EXIT;
	}
}
// タイトルシーンの描画
void DrawTitleScene()
{
	DrawExtendGraph(0, 0, 1920, 1080, titleImage, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220); // 少し濃さ調整
	DrawGraph(0, 0, vignetteHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	startBtn.DrawImage(startButtonImage,showConfirm || isPause);
	continueBtn.DrawImage(continueButtonImage, showConfirm || isPause);
	exitBtn.DrawImage(exitButtonImage, showConfirm || isPause);
}

