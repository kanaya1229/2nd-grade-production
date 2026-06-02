#pragma once

#include "Init.h"
#include "UIButton.h"

enum MemoType
{
    MEMO_NONE,

    MEMO_PHOSPHORUS,
    MEMO_FAIRYBOOK,
    MEMO_DIARY,
    MEMO_FIREDOC,
};

struct Memo
{
    char title[64];
    char text[2048];
    bool unlocked;
};

extern Button bedButton;
extern Button deskButton;
extern Button bookshelfButton;
extern Button doorButton;
extern Button labDoorButton;
extern Button storageDoorButton;
extern Button noteButton;
extern Button fairyBookButton;
extern Button maskButton;
extern Button hoseButton;
extern Button backHallFromLabButton;
extern Button diaryButton;
extern Button pamButton;
extern Button fireDocButton;
extern Button backHallFromStorageButton;

extern bool showMemo;

void InitExploreScene();
void UpdateExploreScene();
void DrawExploreScene();