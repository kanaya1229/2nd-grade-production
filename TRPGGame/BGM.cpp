#include "DxLib.h"
#include "Pause.h"
#include "BGM.h"


// BGM
int bgmTitle;
int bgmExplore;
int bgmBattle;
int bgmEndingHappy;
int bgmEndingBad;
int bgmEndCredit;

// SE
int seDice;
int seButton;
int seSuccess;
int seFail;
int seDamage;
int sePoison;

// åªç›çƒê∂íÜÇÃBGM
int currentBGM = -1;

// BGMÅESEÇì«Ç›çûÇﬁ
void InitSound() {
	bgmTitle = LoadSoundMem("Sound\\Title.mp3");
	bgmExplore = LoadSoundMem("Sound\\Explore.mp3");
	bgmBattle = LoadSoundMem("Sound\\BattleBGM.mp3");
	bgmEndingHappy = LoadSoundMem("Sound\\HappyEnd.mp3");
	bgmEndingBad = LoadSoundMem("Sound\\BadEnd.mp3");
	bgmEndCredit = LoadSoundMem("Sound\\Endcredit.mp3");

	seDice = LoadSoundMem("Sound\\Dice.mp3");
	seButton = LoadSoundMem("Sound\\Button.mp3");
	seSuccess = LoadSoundMem("Sound\\Success.mp3");
	seFail = LoadSoundMem("Sound\\Fail.mp3");
	sePoison = LoadSoundMem("Sound\\Damage1.mp3");
	seDamage = LoadSoundMem("Sound\\Damage2.mp3");
}
// âπó ê›íËÇîΩâfÇ∑ÇÈ
void UpdateSoundVolume()
{
    int bgmVol =
        masterVolume * bgmVolume / 255;

    int seVol =
        masterVolume * seVolume / 255;

    ChangeVolumeSoundMem(bgmVol, bgmTitle);
    ChangeVolumeSoundMem(bgmVol, bgmExplore);
    ChangeVolumeSoundMem(bgmVol, bgmBattle);
    ChangeVolumeSoundMem(bgmVol, bgmEndingHappy);
    ChangeVolumeSoundMem(bgmVol, bgmEndingBad);
    ChangeVolumeSoundMem(bgmVol, bgmEndCredit);

    ChangeVolumeSoundMem(seVol, seDice);
    ChangeVolumeSoundMem(seVol, seButton);
    ChangeVolumeSoundMem(seVol, seSuccess);
    ChangeVolumeSoundMem(seVol, seFail);
    ChangeVolumeSoundMem(seVol, seDamage);
    ChangeVolumeSoundMem(seVol, sePoison);
}
// BGMÇçƒê∂Ç∑ÇÈ
void PlayBGM(int handle)
{
    if (currentBGM == handle)
        return;

    StopSoundMem(bgmTitle);
    StopSoundMem(bgmExplore);
    StopSoundMem(bgmBattle);
    StopSoundMem(bgmEndingHappy);
    StopSoundMem(bgmEndingBad);
    StopSoundMem(bgmEndCredit);

    PlaySoundMem(handle, DX_PLAYTYPE_LOOP);

    currentBGM = handle;
}