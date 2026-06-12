#include "StoryScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "SaveData.h"
#include <tchar.h>

const char* story[] =
{
	{
		"本州から少し離れた、小さな孤島。\n"
		"かつて子どもたちの声で賑わっていたその島は、\n"
		"今では老人ばかりが暮らしていた。"
	},

	{
		"静かな廃島同然となったその場所には、\n"
		"古くから続く奇妙な習慣が存在していた。\n"
		"一年おきに行われる、名も無き儀式。"
	},

	{
		"その夜、儀式は失敗した。\n"
		"熱。\n"
		"毒。"
	},

	{
		"そして悲鳴。\n"
		"島民たちは次々と倒れ、\n"
		"島には炎だけが残された。"
	},

	{
		"――そして今。\n"
		"流れ着いたあなたを待っていたのは、\n"
		"焼け落ちた診療所だった。"
	},

	{
		"閉ざされた扉の奥で蠢く“何か”。\n"
		"熱と毒に満ちた島で、\n"
		"あなたは真実を知ることになる。"
	},

	{
		"ここからはシナリオになります！\n"
		"くれぐれも熱や毒にはお気をつけてください。\n"
		""
	},

	{
		"このゲームは作品をお借りして制作にあてさせていただいております。\n"
		"収益目的ではなく、自分の一つの制作ですので収益化はしません。\n"
		"お貸しいただいたシナリオ『輝きと伏す』　犬小屋三人前/ぽてまと様より　"
	},

	{
		"利用規約にございます収益化はいたしません。\n"
		"ただこのシナリオに感銘を受け改変なしでの\n"
		"ゲーム制作に使用させていただきます。"
	},

	{
		"操作や進行につきましてはESCでの設定画面での操作方法をご確認ください。\n"
		" \n"
		"                                               Press next to start"
	}
};

int prologueBG;

const int STORY_MAX =
sizeof(story) / sizeof(story[0]);

int storyIndex = 0;

int storyFont;

int textCount = 0;

bool textFinish = false;

// 冒頭のストーリーシーンの初期化
void InitStoryScene() {

	prologueBG = LoadGraph("Image\\story.png");

	storyFont =
		CreateFontToHandle(
			"Yu Gothic UI",
			50,
			3);

}
// 冒頭のストーリーシーンのアップデート
void UpdatePrologueScene()
{

	static bool oldClick = false;
	static bool oldPush = false;

	bool nowClick = (IsMousePressedOnce(MOUSE_INPUT_LEFT));
	bool nowPush = (IsKeyPressedOnce(KEY_INPUT_RETURN));

	// それぞれの立ち上がり判定
	bool clickEdge = (nowClick && !oldClick);
	bool pushEdge = (nowPush && !oldPush);

	// どっちか押されたら次へ
	bool next = (clickEdge || pushEdge);

	const char* text = story[storyIndex];

	if (!textFinish)
	{
		textCount++;

		int len = strlen(text);

		if (textCount >= len)
		{
			textCount = len;
			textFinish = true;
		}

		if (next)
		{
			textCount = len;
			textFinish = true;
		}
	}
	else
	{
		if (next)
		{
			storyIndex++;
			textCount = 0;
			textFinish = false;
		}
	}

	// 更新
	oldClick = nowClick;
	oldPush = nowPush;

	if (storyIndex >= STORY_MAX)
	{
		player.storyCleared = true;

		currentScene = SCENE_GAMEIN;

		SaveGame(currentSlot);
		return;
	}
}
// 冒頭のストーリーシーンの描画
void DrawPrologueScene()
{
	DrawExtendGraph(
		0,
		0,
		1920,
		1080,
		prologueBG,
		TRUE);

	// ウィンドウ
	SetDrawBlendMode(
		DX_BLENDMODE_ALPHA,
		180);

	DrawBox(
		40,
		780,
		1880,
		1030,
		GetColor(0, 0, 0),
		TRUE);

	SetDrawBlendMode(
		DX_BLENDMODE_NOBLEND,
		0);

	// 枠
	DrawBox(
		40,
		780,
		1880,
		1030,
		GetColor(255, 255, 255),
		FALSE);

	const char* text = story[storyIndex];

	char temp[1024] = {};
	memcpy(temp, text, textCount);
	temp[textCount] = '\0';

	DrawNovelText(
		120,
		820,
		temp,        // ←そのまま文字列
		60,          // ←行間（ここだけ調整）
		GetColor(255, 255, 255),
		storyFont);

	DrawString(
		1700,
		1000,
		"CLICK OR ENTER",
		GetColor(180, 180, 180));
}