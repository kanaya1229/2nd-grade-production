#pragma once

#include "DxLib.h"
#include <string>
// 画像やBoxでのボタンの処理クラス
class Button
{

public:

    int x, y, w, h;

    Button(int _x, int _y, int _w, int _h);

    bool prevMouseDown = false;

    bool IsHovered();
    bool IsClicked();

    void Draw(bool locked);
    void DrawImage(int image, bool locked);
    void DrawArea();
    void DrawLabel(const char* text);
};