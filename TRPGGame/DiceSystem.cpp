#include "DiceSystem.h"
#include "DxLib.h"
#include "BGM.h"

int diceImage[6];

bool rolling = false;

int diceResult = 1;

int diceFrame = 0;

int displayFace = 1;

int diceVisibleTimer = 0;

bool pendingSuccess = false;

void InitDiceUI()
{
    diceImage[0] = LoadGraph("Image\\Dice1.png");
    diceImage[1] = LoadGraph("Image\\Dice2.png");
    diceImage[2] = LoadGraph("Image\\Dice3.png");
    diceImage[3] = LoadGraph("Image\\Dice4.png");
    diceImage[4] = LoadGraph("Image\\Dice5.png");
    diceImage[5] = LoadGraph("Image\\Dice6.png");
}

void StartDiceAnimation(int result)
{
    PlaySoundMem(
        seDice,
        DX_PLAYTYPE_BACK);

    rolling = true;

    diceResult = result;

    if (diceResult < 1)
        diceResult = 1;

    if (diceResult > 6)
        diceResult = 6;

    diceFrame = 0;

    diceVisibleTimer = 180; // –ñ1.5•b
}

void UpdateDiceUI()
{
    if (rolling)
    {
        diceFrame++;

        displayFace = GetRand(5) + 1;
        if (diceFrame > 40)
        {
            rolling = false;
            displayFace = diceResult;

            if (pendingSuccess)
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

bool IsDiceRolling()
{
    return rolling;
}