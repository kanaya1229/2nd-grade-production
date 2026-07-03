#include "DxLib.h"
#include "SceneManager.h"
#include "SaveData.h"

char inputName[32] = "";        // 入力中の名前
int nameLength = 0;             // 名前の文字数
bool oldKeys[256] = { false };  // キー入力状態
int nameFont;                   // 名前入力用フォント

// 指定されたキーのアルファベットを検索
void AddChar(int key, const char* str)
{
    bool now = CheckHitKey(key);

    if (now && !oldKeys[key])
    {
        if (strlen(inputName) < 10)
        {
            strcat_s(inputName, str);
        }
    }

    oldKeys[key] = now;
}

// セーブデータの名前のシーンアップデート
void UpdateNameScene()
{
    // アルファベット
    AddChar(KEY_INPUT_A, "A");
    AddChar(KEY_INPUT_B, "B");
    AddChar(KEY_INPUT_C, "C");
    AddChar(KEY_INPUT_D, "D");
    AddChar(KEY_INPUT_E, "E");
    AddChar(KEY_INPUT_F, "F");
    AddChar(KEY_INPUT_G, "G");
    AddChar(KEY_INPUT_H, "H");
    AddChar(KEY_INPUT_I, "I");
    AddChar(KEY_INPUT_J, "J");
    AddChar(KEY_INPUT_K, "K");
    AddChar(KEY_INPUT_L, "L");
    AddChar(KEY_INPUT_M, "M");
    AddChar(KEY_INPUT_N, "N");
    AddChar(KEY_INPUT_O, "O");
    AddChar(KEY_INPUT_P, "P");
    AddChar(KEY_INPUT_Q, "Q");
    AddChar(KEY_INPUT_R, "R");
    AddChar(KEY_INPUT_S, "S");
    AddChar(KEY_INPUT_T, "T");
    AddChar(KEY_INPUT_U, "U");
    AddChar(KEY_INPUT_V, "V");
    AddChar(KEY_INPUT_W, "W");
    AddChar(KEY_INPUT_X, "X");
    AddChar(KEY_INPUT_Y, "Y");
    AddChar(KEY_INPUT_Z, "Z");

    // BackSpace
    if (IsKeyPressedOnce(KEY_INPUT_BACK))
    {
        int len = strlen(inputName);

        if (len > 0)
        {
            inputName[len - 1] = '\0';
        }
    }

    // Enter
    if (IsKeyPressedOnce(KEY_INPUT_RETURN))
    {
        if (strlen(inputName) > 0)
        {
            strcpy_s(player.name, inputName);

            SaveGame(currentSlot);
            LoadAllSaveData();
            currentScene = SCENE_STARTGAME;
        }
    }
}
// セーブデータの名前のシーン描画
void DrawNameScene()
{

    DrawBox(
        0, 0,
        1920, 1080,
        GetColor(10, 10, 10),
        TRUE);

    // タイトル
    DrawStringToHandle(
        760,
        250,
        "INPUT NAME",
        GetColor(255, 255, 255),
        nameFont);

    // 入力欄
    int boxW = 1000;
    int boxH = 180;

    int left = 960 - boxW / 2;
    int top = 540 - boxH / 2;
    int right = left + boxW;
    int bottom = top + boxH;

    // 背景
    DrawBox(
        left,
        top,
        right,
        bottom,
        GetColor(20, 20, 20),
        TRUE);

    // 枠
    DrawBox(
        left,
        top,
        right,
        bottom,
        GetColor(255, 255, 255),
        FALSE);

    // 名前表示
    DrawStringToHandle(
        left + 120,
        top + 55,
        inputName,
        GetColor(0, 255, 0),
        nameFont);

    // 説明
    DrawString(
        690,
        760,
        "ENTER : CONFIRM   BACKSPACE : DELETE",
        GetColor(180, 180, 180));
}