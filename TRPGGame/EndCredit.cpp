#include "EndCredit.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "BGM.h"

static int creditY;
static int creditFont;

static bool finished = false;

const char* creditLines[] =
{
    "━━━━━━━━━━━━━━━━━━━━━",
    "",
    "輝きと伏す",
    "",
    "━━━━━━━━━━━━━━━━━━━━━",
    "",
    "",
    "Programming & Design",
    "",
    "田中 快人",
    "",
    "",
    "━━━━━━━━━━━━━━━━━━━━━",
    "",
    "Original Scenario",
    "",
    "『輝きと伏す』",
    "",
    "犬小屋三人前 / ぽてまと 様",
    "",
    "素晴らしいシナリオをありがとうございました",
    "",
    "━━━━━━━━━━━━━━━━━━━━━",
    "",
    "音源提供",
    "",
    "楽曲：柊情景音楽店様",
    "",
    "効果音：効果音ラボ様、音人様",
    "",
    "音源の提供ありがとうございます",
    "",
    "━━━━━━━━━━━━━━━━━━━━━",
    "",
    "",
    "Development Tools",
    "",
    "DxLib",
    "",
    "Visual Studio",
    "",
    "C++",
    "",
    "",
    "━━━━━━━━━━━━━━━━━━━━━",
    "",
    "不明点や配列化などの作業",
    "",
    "Google Gemini",
    "",
    "ChatGPT",
    "",
    "使用したAIアシスタント",
    "",
    "━━━━━━━━━━━━━━━━━━━━━",
    "",
    "",
    "And You...",
    "",
    "このゲームを最後まで遊んでくださった",
    "",
    "あなたへ",
    "",
    "心より感謝いたします",
    "",
    "",
    "",
    "━━━━━━━━━━━━━━━━━━━━━",
    "",
    "Thank you for Playing",
    "",
    "━━━━━━━━━━━━━━━━━━━━━",
    "",
    "",
    "",
    "ENTER でタイトルに戻ります。",
    "",
    "",
    "",
    "━━━━━━━━━━━━━━━━━━━━━"
};

const int CREDIT_LINE_COUNT =
sizeof(creditLines) / sizeof(creditLines[0]);

void InitEndCredit()
{
    creditFont =
        CreateFontToHandle(
            "Yu Gothic UI",
            48,
            3);
}

void StartEndCredit()
{
    creditY = 1080;

    finished = false;
}

void UpdateEndCredit()
{
    PlayBGM(bgmEndCredit);

    creditY -= 1;

    if (creditY < -2500)
    {
        finished = true;
    }
}

void DrawEndCredit()
{
    DrawBox(
        0,
        0,
        1920,
        1080,
        GetColor(0, 0, 0),
        TRUE);

    for (int i = 0; i < CREDIT_LINE_COUNT; i++)
    {
        int w =
            GetDrawStringWidthToHandle(
                creditLines[i],
                strlen(creditLines[i]),
                creditFont);

        DrawStringToHandle(
            (1920 - w) / 2,
            creditY + i * 60,
            creditLines[i],
            GetColor(255, 255, 255),
            creditFont);
    }
}