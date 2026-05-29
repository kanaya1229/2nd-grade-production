#pragma once
#include "ExploreScene.h"


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

    bool hasMask;
    bool hasHose;
    bool hasPAM;

    bool checkedBed;
    bool checkedDesk;
    bool checkedBookshelf;

    bool checkedFairyBook;
    bool checkedMask;
    bool checkedHose;

    bool checkedDiary;
    bool checkedPam;
    bool checkedFireDoc;

    bool checkedLab;
    bool checkedStorage;

    bool finalEventStarted;

    // エンディング管理
    int endingType;
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