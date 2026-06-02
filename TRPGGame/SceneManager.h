#include "Dxlib.h"

#pragma once

// ゲーム画面
enum Scene
{
    SCENE_TITLE,
    SCENE_SAVESELECT,
    SCENE_STATUS,
    SCENE_NAME,
    SCENE_STARTGAME,
    SCENE_GAMEIN,
    SCENE_GAMEFIGHT,
};
// セーブ or ロード
enum SaveMode
{
    MODE_NEW_GAME,
    MODE_LOAD_GAME
};
// ステータス選択
enum StatusMode
{
    STATUS_EDIT,
    STATUS_VIEW
};


extern StatusMode statusMode;
extern SaveMode saveMode;
extern Scene currentScene;