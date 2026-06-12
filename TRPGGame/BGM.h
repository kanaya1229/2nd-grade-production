#pragma once

// BGM
extern int bgmTitle;
extern int bgmExplore;
extern int bgmBattle;
extern int bgmEndingHappy;
extern int bgmEndingBad;
extern int bgmEndCredit;

// SE
extern int seDice;
extern int seButton;
extern int seSuccess;
extern int seFail;
extern int seDamage;
extern int sePoison;



void InitSound();
void UpdateSoundVolume();
void PlayBGM(int handle);