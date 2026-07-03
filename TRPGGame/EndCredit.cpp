#include "EndCredit.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "BGM.h"

static int creditY;     // クレジットの表示位置
static int creditFont;  // クレジット用フォント

static bool finished = false;// クレジット終了フラグ

// クレジット表示内容
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
    "柊情景音楽店様 : https://hiiragimusic.com/",
    "",
    "効果音：効果音ラボ様、音人様",
    "",
    "効果音ラボ様 : https://soundeffect-lab.info/",
    "",
    "音人様 : https://on-jin.com/",
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
    "使用したAIアシスタント",
    "",
    "不明点や配列化などの作業",
    "",
    "Google Gemini",
    "",
    "ChatGPT",
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
};                    // クレジット表示内容
// クレジット行数
const int CREDIT_LINE_COUNT =
sizeof(creditLines) / sizeof(creditLines[0]);
// クレジット用フォントを作成する
void InitEndCredit()
{
    creditFont =
        CreateFontToHandle(
            "Yu Gothic UI",
            48,
            3);
}
// クレジットを開始する
void StartEndCredit()
{
    creditY = 1080;

    finished = false;
}
// クレジットのスクロールを更新する
void UpdateEndCredit()
{
    PlayBGM(bgmEndCredit);

    creditY -= 1;

    if (creditY < -2500)
    {
        finished = true;
    }
}
// クレジットを描画する
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