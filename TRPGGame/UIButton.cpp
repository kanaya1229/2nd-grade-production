#include "UIButton.h"
#include "DxLib.h"
#include "ConfirmWindow.h"


Button::Button(int _x, int _y, int _w, int _h)
{
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}
// ボタンにマウスが触れていたら
bool Button::IsHovered()
{
    int mx, my;
    GetMousePoint(&mx, &my);

    return mx >= x &&
        mx <= x + w &&
        my >= y &&
        my <= y + h;
}
// ボタンをクリックしたら
bool Button::IsClicked()
{
    bool mouseDownNow =
        IsHovered() &&
        (GetMouseInput() & MOUSE_INPUT_LEFT);

    int mx, my;

    GetMousePoint(&mx, &my);
    bool clicked = false;

    if (mx >= x && mx <= x + w &&
        my >= y && my <= y + h)
    {
        // 「押されてた → 離した瞬間」
        clicked = (!mouseDownNow && prevMouseDown);
    }

    prevMouseDown = mouseDownNow;

    return clicked;
}
// ボタンの描画
void Button::Draw(bool locked)
{
    int color = GetColor(70, 70, 70);

    if (IsHovered() && !locked)
    {
        color = GetColor(120, 120, 255);
    }

    DrawBox(x, y, x + w, y + h, color, TRUE);

}
// ボタン画像での描画
void Button::DrawImage(int image,bool locked)
{
    DrawExtendGraph(x, y, x + w, y + h, image, TRUE);

    if (IsHovered() && !locked)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
        DrawBox(x, y, x + w, y + h, GetColor(255, 255, 255), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

// 調べられる場所を光らせる
void Button::DrawArea()
{
    if (IsHovered())
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);

        DrawBox(
            x,
            y,
            x + w,
            y + h,
            GetColor(255, 255, 255),
            TRUE);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

// ラベル表示
void Button::DrawLabel(const char* text)
{
    if (IsHovered())
    {
        int mx, my;

        GetMousePoint(&mx, &my);

        DrawBox(
            mx + 15,
            my - 10,
            mx + 170,
            my + 30,
            GetColor(20, 20, 20),
            TRUE);

        DrawString(
            mx + 25,
            my,
            text,
            GetColor(255, 255, 255));
    }
}