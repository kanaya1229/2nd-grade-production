#pragma once
#include "ExploreScene.h"
#include "BattleScene.h"


// ゲーム終了フラグ
extern bool exitFlag;

enum RoomType
{
	ROOM_FIRST,
	ROOM_HALL,
	ROOM_LAB,
	ROOM_STORAGE,
};

// プレイヤーのステータス
struct PlayerData
{
	char name[32];// ゲーム名

	int stage;// ストーリー進行度を記録
	int hp;   // 設定可能なHP

	// 基本ステータス（最大20）
	int str; // 筋力
	int con; // 体力
	int pow; // 精神力
	int dex; // 敏捷性
	int app; // 外見
	int siz; // 体格
	int intel; // 知性
	int edu; // 教育

	// 追加ステータス(最大４)
	int tec; // 器用
	int knw; // 知識
	int insight; // 洞察

	int selectStatus;//ステータスのインデックス
	int remainPoint;//最大割り振りポイント

	int savedStoryIndex;// 冒頭のストーリーの文字数
	bool storyCleared;  // 冒頭のストーリークリア判定

	RoomType currentRoom;
	
	// ベット
	bool checkedBed;

	// 机
	bool checkedDesk;
	bool readDoc1;
	bool readDoc2;
	bool readDoc3;
	bool foundLeftMemo;
	int deskSearchCount;

	// 本棚
	bool checkedBookshelf;
	bool checkedChemBook;
	bool checkedPictureBook;
	bool foundGap;
	bool foundMissingBook;
	bool bookshelfMenu;

	// 研究室
	bool checkedLab;
	bool labcheckeddeskall;
	bool hasMask;
	bool readObserveDetail;
	bool checkedLabDesk;
	bool checkedNotebook;
	bool checkedMatchBook;
	bool foundBurnMark;
	bool checkedShelf;
	bool checkedCopyPaper;
	bool checkedSink;
	bool labDeskMenu;
	// 倉庫
	bool hasPAM;
	bool checkedDiary;
	bool readDiary;
	bool checkedFireDoc;
	bool readFireDoc;
	bool foundLetter;
	bool foundPamMissing;

	bool bossDoorReady;
	bool canEnterBossRoom;
};

// ゲーム音量
extern int masterVolume;
extern int bgmVolume;
extern int seVolume;

// ゲーム音声
extern int masterSoundHandle;
extern int bgmSoundHandle;
extern int seSoundHandle;

PlayerData CreateDefaultPlayer();
void DrawNovelText(
	int x, int y,
	const char* text,
	int lineHeight,
	int color,
	int fontHandle);
bool IsKeyPressedOnce(int key);
bool IsMousePressedOnce(int button);