#include "EndingScene.h"
#include "BattleScene.h"
#include "DxLib.h"
#include "UIButton.h"
#include "Init.h"
#include "SaveData.h"
#include "StoryScene.h"
#include "SceneManager.h"
#include "EndCredit.h"

EndingType currentEnding;		// 現在のエンディング種別

int endingIndex = 0;			// 表示中の文章番号
int endingTextCount = 0;		// 文字送りの表示数
bool endingTextFinish = false;	// 文章表示完了フラグ

// 背景画像
int endingImage1;
int endingImage1A;
int endingImage2;
int endingImage3;
// 背景フェード用アルファ値
int imageAlpha = 0;
// END1の文章データ
const char* END1_TEXT[] =
{
	"END1\n\n"
	"『輝きと伏す』",

	"あなたは消火器を噴射した。\n"
	"空気が震えるほどの叫び声が\n"
	"あたり一面に響き渡る。",

	"その叫びは泣き声のようでもあり、\n"
	"悲鳴のようでもあり、\n"
	"歓声のようでもあった。",

	"白く輝く異形は激しく蠢き、\n"
	"苦しむように震えている。",

	"炎が消えていく。\n"
	"輝きが褪せていく。",

	"やがて異形は黒い塊となり、\n"
	"完全に動きを止めた。",

	"その姿を見て初めて、\n"
	"炎の塊が人の形をしていたことに\n"
	"あなたは気付く。",

	"前方の火勢も弱まっている。\n"
	"今なら安全に出口へ向かえそうだ。",

	"あなたは建物の外へ出た。",

	"そこに広がっていたのは、\n"
	"小さく荒れ果てた島だった。",

	"夜の鳥が鳴いている。\n"
	"波の音が聞こえる。",

	"あなたは確かに生きている。",

	"遠くには本州の灯りが見えた。",

	"帰る方法はきっとある。",

	"背後では炎が爆ぜる音が続く。",

	"だが今は前へ進もう。",

	"END1\n"
	"『輝きと伏す』"
};
// END1の文章数
const int END1_COUNT =
sizeof(END1_TEXT) / sizeof(END1_TEXT[0]);
// END1-Aの文章データ
const char* END1A_TEXT[] =
{
	"END1-A\n\n"
	"『輝きは臥い伏す』",

	"あなたはホースを手に取り、\n"
	"大量の水を浴びせた。",

	"空気が震えるほどの叫び声が\n"
	"建物全体に響き渡る。",

	"異形は苦しむように蠢き続ける。",

	"炎が消えていく。\n"
	"輝きが褪せていく。",

	"やがて異形は黒い塊となり、\n"
	"完全に動きを止めた。",

	"前方の炎も沈静化している。",

	"今なら出口へ向かうことができる。",

	"あなたは建物の外へ出た。",

	"そこには小さな島が広がっていた。",

	"夜の鳥が鳴いている。\n"
	"波の音が聞こえる。",

	"あなたは生還した。",

	"遠くには本州の灯りが見える。",

	"帰る方法はきっと見つかるだろう。",

	"END1-A\n"
	"『輝きは臥い伏す』"
};
// END1-Aの文章数
const int END1A_COUNT =
sizeof(END1A_TEXT) / sizeof(END1A_TEXT[0]);
// END2の文章データ
const char* END2_TEXT[] =
{
	"END2\n\n"
	"『輝きは消えない』",

	"あなたは炎を避けながら走った。",

	"今は逃げることだけを考える。",

	"異形も炎も置き去りにした。",

	"前方の扉はあっさりと開いた。",

	"冷たい夜風が肺に流れ込む。",

	"外には小さな島が広がっていた。",

	"夜の鳥が鳴いている。\n"
	"波の音が聞こえる。",

	"あなたは今も生きている。",

	"遠くには本州の灯り。",

	"ボートも見える。\n"
	"電話も見つかるかもしれない。",

	"帰る方法はきっとある。",

	"しかし背後では今も炎が燃えている。",

	"あの輝きは消えない。",

	"熱を持ったまま、\n"
	"静かにそこに在り続ける。",

	"END2\n"
	"『輝きは消えない』"
};
// END2の文章数
const int END2_COUNT =
sizeof(END2_TEXT) / sizeof(END2_TEXT[0]);
// END3の文章データ
const char* END3_TEXT[] =
{
	"END3\n\n"
	"『輝きと伏す』",

	"肺が痛い。",

	"呼吸ができない。",

	"身体が熱い。",

	"視界が歪んでいく。",

	"あなたはその場へ倒れ込んだ。",

	"炎が身体を焼く。",

	"しかしもう立ち上がれない。",

	"意識がゆっくりと遠のいていく。",

	"最後に見えたのは。",

	"白く輝く異形だった。",

	"その輝きだけが、\n"
	"闇の中で揺れている。",

	"あなたの意識はそこで途切れた。",

	"探索者ロスト",

	"END3\n"
	"『輝きと伏す』"
};
// END3の文章数
const int END3_COUNT =
sizeof(END3_TEXT) / sizeof(END3_TEXT[0]);
// 現在のエンディング文章数を取得する
int GetEndingCount()
{
	switch (currentEnding)
	{
	case ENDING_1:
		return END1_COUNT;

	case ENDING_1A:
		return END1A_COUNT;

	case ENDING_2:
		return END2_COUNT;

	case ENDING_3:
		return END3_COUNT;
	}

	return 0;
}
// 現在表示する文章を取得する
const char* GetCurrentEndingText()
{
	int max = GetEndingCount();

	if (endingIndex < 0 || endingIndex >= max)
	{
		return "";
	}

	switch (currentEnding)
	{
	case ENDING_1:
		return END1_TEXT[endingIndex];

	case ENDING_1A:
		return END1A_TEXT[endingIndex];

	case ENDING_2:
		return END2_TEXT[endingIndex];

	case ENDING_3:
		return END3_TEXT[endingIndex];
	}

	return "";
}
// エンディングを開始する
void StartEnding(EndingType type)
{
	currentEnding = type;

	endingIndex = 0;
	endingTextCount = 0;
	endingTextFinish = false;

	endingImage1 =
		LoadGraph("Image\\End1.png");

	endingImage1A =
		LoadGraph("Image\\End1-A.png");

	endingImage2 =
		LoadGraph("Image\\End2.png");

	endingImage3 =
		LoadGraph("Image\\End3.png");


	imageAlpha = 0;
}
// エンディングの進行を更新する
void UpdateEnding()
{

	if (imageAlpha < 255)
	{
		imageAlpha += 4;

		if (imageAlpha >= 255)
		{
			imageAlpha = 255;
		}
	}
	bool next =
		IsMousePressedOnce(MOUSE_INPUT_LEFT) ||
		IsKeyPressedOnce(KEY_INPUT_RETURN);

	const char* text =
		GetCurrentEndingText();

	if (!endingTextFinish)
	{
		endingTextCount++;

		int len = strlen(text);

		if (endingTextCount >= len)
		{
			endingTextCount = len;
			endingTextFinish = true;
		}

		if (next)
		{
			endingTextCount = len;
			endingTextFinish = true;
		}
	}
	else
	{
		if (next)
		{
			if (endingIndex >= GetEndingCount() - 1)
			{
				StartEndCredit();
				currentScene = SCENE_END;
				return;
			}

			endingIndex++;

			endingTextCount = 0;
			endingTextFinish = false;
		}
	}
}
// エンディング画面を描画する
void DrawEnding()
{

	int imageHandle = -1;

	switch (currentEnding)
	{
	case ENDING_1:
		imageHandle = endingImage1;
		break;

	case ENDING_1A:
		imageHandle = endingImage1A;
		break;

	case ENDING_2:
		imageHandle = endingImage2;
		break;

	case ENDING_3:
		imageHandle = endingImage3;
		break;
	}
	DrawExtendGraph(
		0,
		0,
		1920,
		1080,
		imageHandle,
		TRUE);


	SetDrawBlendMode(
		DX_BLENDMODE_ALPHA,
		255 - imageAlpha);

	DrawBox(
		0,
		0,
		1920,
		1080,
		GetColor(0, 0, 0),
		TRUE);

	SetDrawBlendMode(
		DX_BLENDMODE_NOBLEND,
		0);


	const char* text =
		GetCurrentEndingText();

	char temp[2048] = {};

	memcpy(
		temp,
		text,
		endingTextCount);

	temp[endingTextCount] = '\0';

	DrawBox(
		40,
		760,
		1880,
		1030,
		GetColor(0, 0, 0),
		TRUE);

	DrawNovelText(
		120,
		820,
		temp,
		60,
		GetColor(255, 255, 255),
		storyFont);

	DrawString(
		1700,
		1000,
		"CLICK OR ENTER",
		GetColor(180, 180, 180));
}