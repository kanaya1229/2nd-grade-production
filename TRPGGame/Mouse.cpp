#include "DxLib.h"
#include "Mouse.h"
#include "SceneManager.h"
#include "ExploreScene.h"
#include "UIButton.h"
#include "SaveData.h"
#include "Pause.h"

int cursorImage;
int cursorSearch;

bool isSearchCursor = false;

bool IsAnyHovered()
{

    if (currentScene == SCENE_GAMEIN) {
        switch (player.currentRoom)
        {
        case ROOM_FIRST:

            return
                bedButton.IsHovered() ||
                deskButton.IsHovered() ||
                bookshelfButton.IsHovered() ||
                doorButton.IsHovered();

        case ROOM_HALL:

            return
                labDoorButton.IsHovered() ||
                storageDoorButton.IsHovered() ||
                noteButton.IsHovered();

        case ROOM_LAB:

            return
                labDeskButton.IsHovered() ||
                labShelfButton.IsHovered() ||
                hoseButton.IsHovered() ||
                backHallFromLabButton.IsHovered();

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

    if (isSearchCursor && !showMemo && !isPause)
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