#pragma once


#pragma once

enum ConfirmType
{
    CONFIRM_NONE,
    CONFIRM_DELETE,
    CONFIRM_EXIT,
    CONFIRM_TITLE
};

extern bool showConfirm;
extern bool GameEnd;

extern ConfirmType confirmType;

extern int targetSlot;

void UpdateConfirm();

void DrawConfirm();