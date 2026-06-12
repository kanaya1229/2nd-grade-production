#pragma once

#include "Init.h"
#include "UIButton.h"


enum MemoType
{
    MEMO_NONE,

    MEMO_DOC1,
    MEMO_DOC2,
    MEMO_DOC3,

    MEMO_OBSERVE_NOTE,
    MEMO_FAIRYBOOK,
    MEMO_COPY_PAPER,
    MEMO_DIARY,
    MEMO_FIREDOC
};

enum PlayerFace
{
    FACE_NORMAL,
    FACE_THINK,
    FACE_DAMAGE
};

extern PlayerFace playerFace;

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

extern Button chemistryBookButton;
extern Button pictureBookButton;
extern Button closeBookshelfButton;

extern Button labDoorButton;
extern Button storageDoorButton;
extern Button noteButton;

extern Button NoteBookButton;
extern Button labDeskButton;
extern Button matchBookButton;
extern Button DeskbackButton;

extern Button labShelfButton;
extern Button hoseButton;

extern Button diaryButton;
extern Button pamButton;
extern Button fireDocButton;

extern Button backHallFromLabButton;
extern Button backHallFromStorageButton;

extern Button memoBackButton;
extern Button memoDoc1Button;
extern Button memoDoc2Button;
extern Button memoDoc3Button;
extern Button memoBookButton;


extern MemoType currentMemo;
extern bool showMemo;

void DrawPlayer();
void UpdatePlayerFace();
bool SkillCheck(int skill);
int RollDice(int max);
void InitExploreScene();
void UpdateExploreScene();
void DrawExploreScene();