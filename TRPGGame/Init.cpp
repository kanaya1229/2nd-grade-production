#include "DxLib.h"
#include "Init.h"

// プレイヤーの初期化
PlayerData CreateDefaultPlayer()
{
	PlayerData p{};

	strcpy_s(p.name, "");
	// ステータスの初期値
	p.stage = 1;
	p.hp = 20;

	p.str = 10;
	p.con = 10;
	p.pow = 10;
	p.dex = 10;
	p.app = 10;
	p.siz = 10;
	p.intel = 10;
	p.edu = 10;

	p.tec = 2;
	p.knw = 2;
	p.insight = 2;

	// 最大ステータス
	p.selectStatus = 0;
	p.remainPoint = 42;

	// 冒頭
	p.savedStoryIndex = 0;
	p.storyCleared = false;

	// 探索
	p.currentRoom = ROOM_FIRST;
	// ベット
	p.checkedBed = false;
	// 机
	p.checkedDesk = false;
	p.readDoc1 = false;
	p.readDoc2 = false;
	p.readDoc3 = false;
	p.foundLeftMemo = false;
	p.deskSearchCount = 0;
	// 本棚
	p.checkedBookshelf = false;
	p.checkedChemBook = false;
	p.checkedPictureBook = false;
	p.foundGap = false;
	p.foundMissingBook = false;
	p.bookshelfMenu = false;
	// 研究所
	p.checkedLab = false;
	p.readObserveDetail = false;
	p.labcheckeddeskall = false;
	p.hasMask = false;
	p.checkedLabDesk = false;
	p.checkedNotebook = false;
	p.checkedMatchBook = false;
	p.foundBurnMark = false;
	p.checkedShelf = false;
	p.checkedCopyPaper = false;
	p.labDeskMenu = false;
	p.checkedSink = false;


	
	p.hasPAM = false;
	p.checkedDiary = false;
	p.readDiary = false;
	p.readFireDoc = false;
	p.checkedFireDoc = false;


	p.bossDoorReady = false;
	p.canEnterBossRoom = false;

	return p;
}

// 文字を一文字ずつ描画する
void DrawNovelText(
	int x, int y,
	const char* text,
	int lineHeight,
	int color,
	int font)
{
	char buf[2048] = {};
	strcpy_s(buf, text);

	int lineY = y;

	char* ctx = nullptr;
	char* line = strtok_s(buf, "\n", &ctx);

	while (line != nullptr)
	{
		DrawStringToHandle(
			x,
			lineY,
			line,
			color,
			font);

		lineY += lineHeight;

		line = strtok_s(nullptr, "\n", &ctx);
	}
}

bool IsKeyPressedOnce(int key)
{
	static bool oldKeys[256] = { false };

	bool now = CheckHitKey(key);

	bool pressed = (now && !oldKeys[key]);

	oldKeys[key] = now;

	return pressed;
}

bool IsMousePressedOnce(int button)
{
	static int oldMouse = 0;

	int nowMouse = GetMouseInput();

	bool pressed =
		((nowMouse & button) &&
			!(oldMouse & button));

	oldMouse = nowMouse;

	return pressed;
}