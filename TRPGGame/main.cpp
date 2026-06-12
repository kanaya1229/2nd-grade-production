#include "DxLib.h"

#include "SceneManager.h"
#include "TitleScene.h"
#include "SaveData.h"
#include "Mouse.h"
#include "Init.h"
#include "Status.h"
#include "NameScene.h"
#include "ConfirmWindow.h"
#include "StoryScene.h"
#include "Pause.h"
#include "ExploreScene.h"

#include <time.h>

// メイン関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(FALSE);

    SetGraphMode(1920, 1080, 32);

    DxLib_Init();
    // ゲームの初期化
    CursorInit();
    InitTitleScene();
    InitStoryScene();
    InitExploreScene();
    srand((unsigned int)time(NULL));
    nameFont = CreateFontToHandle(
        NULL,
        56,
        3);
    
    // セーブデータのロード
    LoadSettings();
    LoadAllSaveData();
    
    SetDrawScreen(DX_SCREEN_BACK);

    while (ProcessMessage() == 0)
    {
        // サウンド設定
        ChangeVolumeSoundMem(masterVolume, masterSoundHandle);
        ChangeVolumeSoundMem(bgmVolume, bgmSoundHandle);
        ChangeVolumeSoundMem(seVolume, seSoundHandle);

        // デバックキーと条件でゲーム終了
        if ((GameEnd) || CheckHitKey(KEY_INPUT_RETURN) &&
            (CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_RSHIFT)))
        {
            break;
        }

        // マウスポイント
        int mx, my;
        GetMousePoint(&mx, &my);

        ClearDrawScreen();

        // 画面遷移
        switch (currentScene)
        {
        case SCENE_TITLE:
            UpdateTitleScene();
            DrawTitleScene();
           
            break;

        case SCENE_SAVESELECT:
            UpdateSaveSelectScene();
            DrawSaveScene();
            break;

        case SCENE_STATUS:
            UpdateStatusScene();
            DrawStatusScene();
            break;

        case SCENE_NAME:
            UpdateNameScene();
            DrawNameScene();
            break;

        case SCENE_STARTGAME:

            UpdatePrologueScene();
            DrawPrologueScene();
            break;

        case SCENE_GAMEIN:

            UpdateExploreScene();
            DrawExploreScene();
            break;
        }

        // ポーズ画面
        if (isPause)
        {
            UpdateSettings();
            DrawSettings();
        }

        // Escでポーズ
        if (!isPause && IsKeyPressedOnce(KEY_INPUT_ESCAPE))
        {
            isPause = true;
        }

        // 注意画面
        UpdateConfirm();
        DrawConfirm();

        // カーソル表示
        DrawCursor();

        ScreenFlip();
    }

    DxLib_End();

    return 0;
}