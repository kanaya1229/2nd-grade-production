#pragma once

extern bool IsRolling;

extern int diceResult;

extern int diceFrame;

extern int displayFace;

extern bool IsPendingSuccess;


void InitDiceUI();
void StartDiceAnimation(int result);
void UpdateDiceUI();
void DrawDiceUI();
bool IsDiceRolling();