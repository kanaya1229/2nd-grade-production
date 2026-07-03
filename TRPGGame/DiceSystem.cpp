#include "DiceSystem.h"
#include "DxLib.h"
#include "BGM.h"

int diceImage[6];               // サイコロ画像
bool IsRolling = false;         // サイコロ演出中フラグ
int diceResult = 1;             // サイコロ結果
int diceFrame = 0;              // 演出フレーム数
int displayFace = 1;            // 表示中の出目
int diceVisibleTimer = 0;       // サイコロ表示時間
bool IsPendingSuccess = false;  // 判定結果フラグ
// サイコロ画像を読み込む
void InitDiceUI()
{
    diceImage[0] = LoadGraph("Image\\Dice1.png");
    diceImage[1] = LoadGraph("Image\\Dice2.png");
    diceImage[2] = LoadGraph("Image\\Dice3.png");
    diceImage[3] = LoadGraph("Image\\Dice4.png");
    diceImage[4] = LoadGraph("Image\\Dice5.png");
    diceImage[5] = LoadGraph("Image\\Dice6.png");
}
// サイコロ演出を開始する
void StartDiceAnimation(int result)
{
    PlaySoundMem(
        seDice,
        DX_PLAYTYPE_BACK);

    IsRolling = true;

    diceResult = result;

    if (diceResult < 1)
        diceResult = 1;

    if (diceResult > 6)
        diceResult = 6;

    diceFrame = 0;

    diceVisibleTimer = 180; // 約1.5秒
}
// サイコロ演出を更新する
void UpdateDiceUI()
{
    if (IsRolling)
    {
        diceFrame++;

        displayFace = GetRand(5) + 1;
        if (diceFrame > 40)
        {
            IsRolling = false;
            displayFace = diceResult;

            if (IsPendingSuccess)
            {
                PlaySoundMem(
                    seSuccess,
                    DX_PLAYTYPE_BACK);
            }
            else
            {
                PlaySoundMem(
                    seFail,
                    DX_PLAYTYPE_BACK);
            }
        }
    }

    if (diceVisibleTimer > 0)
    {
        diceVisibleTimer--;
    }
}
// サイコロを描画する
void DrawDiceUI()
{
    if (diceVisibleTimer <= 0)
        return;

    DrawExtendGraph(
        1500,
        800,
        1700,
        1000,
        diceImage[displayFace - 1],
        TRUE);
}
// サイコロ演出中か判定する
bool IsDiceRolling()
{
    return IsRolling;
}