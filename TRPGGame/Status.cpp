#include "DxLib.h"
#include "Init.h"
#include "Status.h"
#include "SaveData.h"
#include "SceneManager.h"

// ステータスの名前
const char* statusNames[] =
{
    "STR",
    "CON",
    "POW",
    "DEX",
    "APP",
    "SIZ",
    "INT",
    "EDU",
    "TEC",
    "KNW",
    "INSIGHT"
};
// ステータス説明
const char* statusDesc[] =
{
    "筋力：攻撃力や重い物の扱いに影響",
    "体力：HPや耐久力に関係",
    "精神力：状態異常や恐怖耐性",
    "敏捷性：行動速度・回避に影響",
    "外見：NPCの反応や印象",
    "体格：HPや物理耐久に影響",
    "知性：魔法・解析・思考力",
    "教育：知識・スキル習得効率",

    "器用：細かい作業や成功率",
    "知識：情報系スキルの成功率",
    "洞察：隠し要素・嘘の見抜き"
};

// ボタンの判定
bool upKey = false;
bool downKey = false;
bool leftKey = false;
bool rightKey = false;
bool enterKey = false;
bool KeyDawn = false;

// ステータス選択シーンのアップデート
void UpdateStatusScene()
{
    // 現在の入力
    bool nowUp = CheckHitKey(KEY_INPUT_W);
    bool nowDown = CheckHitKey(KEY_INPUT_S);
    bool nowLeft = CheckHitKey(KEY_INPUT_A);
    bool nowRight = CheckHitKey(KEY_INPUT_D);
    bool nowEnter = CheckHitKey(KEY_INPUT_RETURN);

    if (statusMode == STATUS_EDIT)
    {
        // 下
        if (nowDown && !downKey)
        {
            player.selectStatus++;

            if (player.selectStatus > 10)
            {
                player.selectStatus = 0;
            }
        }

        // 上
        if (nowUp && !upKey)
        {
            player.selectStatus--;

            if (player.selectStatus < 0)
            {
                player.selectStatus = 10;
            }
        }

        int* target = nullptr;
        int maxValue = MAX_MAIN;

        switch (player.selectStatus)
        {
        case 0: target = &player.str; break;
        case 1: target = &player.con; break;
        case 2: target = &player.pow; break;
        case 3: target = &player.dex; break;
        case 4: target = &player.app; break;
        case 5: target = &player.siz; break;
        case 6: target = &player.intel; break;
        case 7: target = &player.edu; break;

        case 8:
            target = &player.tec;
            maxValue = MAX_SUB;
            break;

        case 9:
            target = &player.knw;
            maxValue = MAX_SUB;
            break;

        case 10:
            target = &player.insight;
            maxValue = MAX_SUB;
            break;
        }

        // 増加
        if (nowRight && !rightKey)
        {
            if (*target < maxValue && player.remainPoint > 0)
            {
                (*target)++;
                player.remainPoint--;
            }
        }

        // 減少
        if (nowLeft && !leftKey)
        {
            int minValue = 1;

            if (*target > minValue)
            {
                (*target)--;
                player.remainPoint++;
            }
        }
        // 決定
        if (nowEnter && !enterKey)
        {
            SaveGame(currentSlot);

            currentScene = SCENE_NAME;
        }
    }

    if (statusMode == STATUS_VIEW)
    {
        if (nowEnter && !enterKey)
        {
            currentScene = SCENE_GAMEIN;
        }
    }

    // 前フレーム更新
    upKey = nowUp;
    downKey = nowDown;
    leftKey = nowLeft;
    rightKey = nowRight;
    enterKey = nowEnter;
}
// ステータス選択シーンの描画
void DrawStatusScene()
{
    DrawString(400, 50,
        "STATUS SET",
        GetColor(255, 255, 255));

    DrawFormatString(400, 100,
        GetColor(255, 255, 0),
        "POINT : %d",
        player.remainPoint);

    int values[] =
    {
        player.str,
        player.con,
        player.pow,
        player.dex,
        player.app,
        player.siz,
        player.intel,
        player.edu,
        player.tec,
        player.knw,
        player.insight
    };

    for (int i = 0; i < 11; i++)
    {
        int color = GetColor(255, 255, 255);

        if (i == player.selectStatus)
        {
            color = GetColor(0, 255, 0);
        }

        DrawFormatString(
            300,
            180 + i * 40,
            color,
            "%s : %d",
            statusNames[i],
            values[i]);
    }

    DrawBox(
        250,
        700,
        1200,
        820,
        GetColor(20, 20, 20),
        TRUE
    );

    DrawString(
        270,
        730,
        statusDesc[player.selectStatus],
        GetColor(200, 200, 200)
    );

    DrawString(250, 650,
        "WASD : CHANGE / ENTER : START",
        GetColor(255, 255, 255));
}