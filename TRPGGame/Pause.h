#pragma once

enum PauseMode
{
    PAUSE_MENU,
    PAUSE_SETTINGS
};

enum SettingsMode
{
    SETTINGS_MAIN,
    SETTINGS_CONTROL
};

extern bool isPause;

extern int masterVolume;
extern int bgmVolume;
extern int seVolume;

extern bool escEdge;
extern SettingsMode settingsMode;

void UpdateSettings();
void DrawSettings();
void SaveSettings();
void LoadSettings();