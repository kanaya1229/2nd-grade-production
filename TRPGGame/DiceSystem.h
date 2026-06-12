#pragma once

extern bool rolling;

extern int diceResult;

extern int diceFrame;

extern int displayFace;

extern bool pendingSuccess;


void InitDiceUI();
void StartDiceAnimation(int result);
void UpdateDiceUI();
void DrawDiceUI();
bool IsDiceRolling();