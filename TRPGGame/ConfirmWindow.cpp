#include "ConfirmWindow.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "SaveData.h"
#include "UIButton.h"
#include "Pause.h"

// ボタンの座標
Button yesButton(650, 520, 250, 90);
Button noButton(1020, 520, 250, 90);

bool showConfirm = false;// 描画フラグ
bool GameEnd = false;// ゲーム終了フラグ

// DeleteかExitにする構造体
ConfirmType confirmType = CONFIRM_NONE;

// セーブスロットのインデックス
int targetSlot = 0;

// 警告画面のアップデート
void UpdateConfirm()
{
    if (!showConfirm)
    {
        return;
    }

    if (yesButton.IsClicked())
    {

        switch (confirmType)
        {
        case CONFIRM_DELETE:

            DeleteSaveData(targetSlot);

            break;

        case CONFIRM_EXIT:

            GameEnd = true;
            SaveSettings();
            break;

        case CONFIRM_TITLE:

            SaveGame(currentSlot);
            SaveSettings();
            currentScene = SCENE_TITLE;
            isPause = false;
            break;
        }
        showConfirm = false;
        confirmType = CONFIRM_NONE;
    }

    if (noButton.IsClicked())
    {
        showConfirm = false;

        confirmType = CONFIRM_NONE;
    }
}

// 警告画面の描画
void DrawConfirm()
{

    if (!showConfirm)
    {
        return;
    }

    DrawBox(
        500,
        350,
        1420,
        650,
        GetColor(30, 30, 30),
        TRUE);

    DrawBox(
        500,
        350,
        1420,
        650,
        GetColor(255, 255, 255),
        FALSE);

    if (confirmType == CONFIRM_DELETE)
    {
        DrawString(
            700,
            430,
            "このデータを削除しますか？",
            GetColor(255, 80, 80));
    }

    if (confirmType == CONFIRM_EXIT)
    {
        DrawString(
            760,
            430,
            "このゲームを終了しますか？",
            GetColor(255, 255, 255));
    }

    if (confirmType == CONFIRM_TITLE)
    {
        DrawString(
            760,
            430,
            "このゲームを保存して終了しますか？",
            GetColor(255, 255, 255));
    }

    yesButton.Draw(false);
    noButton.Draw(false);

    // YES文字
    DrawString(
        740,
        555,
        "YES",
        GetColor(255, 255, 255));

    // NO文字
    DrawString(
        1135,
        555,
        "NO",
        GetColor(255, 255, 255));
}