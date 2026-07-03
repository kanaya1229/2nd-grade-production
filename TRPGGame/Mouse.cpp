#include "DxLib.h"
#include "Mouse.h"
#include "SceneManager.h"
#include "ExploreScene.h"
#include "UIButton.h"
#include "SaveData.h"
#include "Pause.h"

// カーソル画像
int cursorImage;
int cursorSearch;

// 探索カーソル表示フラグ
bool isSearchCursor = false;

// カーソル変更時の処理
bool IsAnyHovered()
{

    if (currentScene == SCENE_GAMEIN) {
        switch (player.currentRoom)
        {
        case ROOM_FIRST:


            if (!player.bookshelfMenu) {
                return
                    bedButton.IsHovered() ||
                    deskButton.IsHovered() ||
                    bookshelfButton.IsHovered() ||
                    doorButton.IsHovered();
            }
            else {
                return
                    pictureBookButton.IsHovered() ||
                    chemistryBookButton.IsHovered() ||
                    closeBookshelfButton.IsHovered();
            }
                

        case ROOM_HALL:

            return
                labDoorButton.IsHovered() ||
                storageDoorButton.IsHovered() ||
                noteButton.IsHovered();

        case ROOM_LAB:


            if (!player.labDeskMenu) {
                return
                    labDeskButton.IsHovered() ||
                    labShelfButton.IsHovered() ||
                    hoseButton.IsHovered() ||
                    backHallFromLabButton.IsHovered();
            }
            else {
                return
                    matchBookButton.IsHovered() ||
                    NoteBookButton.IsHovered() ||
                    DeskbackButton.IsHovered();
            }

        case ROOM_STORAGE:

            return
                diaryButton.IsHovered() ||
                pamButton.IsHovered() ||
                fireDocButton.IsHovered() ||
                backHallFromStorageButton.IsHovered();

        default:
            return false;
        }
    }
    else {
        return false;
    }
}

// カーソル初期化
void CursorInit() {
    cursorImage = LoadGraph("Image\\mouse.png");
    cursorSearch =
        LoadGraph("Image\\mouse2.png");
}

// カーソル描画
void DrawCursor()
{
    isSearchCursor = IsAnyHovered();

    int mx, my;

    GetMousePoint(&mx, &my);

    int handle = cursorImage;

    double size = 0.05;

    if (isSearchCursor && !IsShowMemo && !isPause)
    {
        handle = cursorSearch;
        size = 0.07;
    }

    DrawRotaGraph(
        mx,
        my,
        size,
        0,
        handle,
        TRUE
    );
}