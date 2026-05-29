#include "DxLib.h"
#include "Init.h"

// ƒvƒŒƒCƒ„[‚Ì‰Šú‰»
PlayerData CreateDefaultPlayer()
{
	PlayerData p{};

	strcpy_s(p.name, "");

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

	p.selectStatus = 0;
	p.remainPoint = 42;

	p.savedStoryIndex = 0;
	p.storyCleared = false;

	// ’Tõ
	p.currentRoom = ROOM_FIRST;

	p.hasMask = false;
	p.hasHose = false;
	p.hasPAM = false;

	p.checkedBed = false;
	p.checkedDesk = false;
	p.checkedBookshelf = false;
	
	p.checkedFairyBook = false;
	p.checkedMask = false;
	p.checkedHose = false;

	p.checkedDiary = false;
	p.checkedPam = false;
	p.checkedFireDoc = false;

	p.checkedLab = false;
	p.checkedStorage = false;

	p.finalEventStarted = false;

	p.endingType = 0;

	return p;
}

// •¶š‚ğˆê•¶š‚¸‚Â•`‰æ‚·‚é
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