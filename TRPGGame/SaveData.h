#include "DxLib.h"
#include "Init.h"

#pragma once

extern PlayerData player;
extern PlayerData saveSlots[4];

extern int currentSlot;

bool LoadGame(int slot);
void SaveGame(int slot);
void LoadAllSaveData();
void UpdateSaveSelectScene();
void DrawSaveScene();
void DeleteSaveData(int slot);