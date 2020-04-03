#ifndef DRAWING
#define DRAWING

#include "threads.h"

#pragma warning(disable : 4244)

#define ABS(x) ((x < 0) ? (-x) : (x))

#define TORAD(x) ((x) * 0.01745329252)

namespace Drawing
{
    void String(int x, int y, char *string, D3DCOLOR color);
    void StringW(int x, int y,  WCHAR *string, D3DCOLOR color);
    void Rect(int x, int y, int width, int height, D3DCOLOR color);
    void BorderedRect(int x, int y, int width, int height, D3DCOLOR colorFill, D3DCOLOR color);
    void Line(int x, int y, int x2, int y2, D3DCOLOR color);
    void DrawLineBordered(int x, int y, int x2, int y2, D3DCOLOR color);
    void FilledLineBox(int x1, int y1, int x2, int y2, D3DCOLOR colorFill);
    void Draw2DBox(int x, int y, int y2, Threads* threads, Blockpost *blockpost, int i, D3DCOLOR color);
    void DrawHealthBar(int x, int y, int height, float health, bool isArmor);
    void FilledRect(int x, int y, int width, int height, D3DCOLOR color);
    void Circle(int x, int y, int radius, D3DCOLOR color);
    void Draw3DBox(D3DXVECTOR3 top, D3DXVECTOR3 bot, int a, int width, int height, float viewMatrix[16], const RECT m_Recr, D3DCOLOR color);
    D3DXCOLOR FromHSB(float hue, float saturation, float brightness);
    D3DXCOLOR QColorToD3DCOLOR(QColor qcolor);
}

namespace Color
{
    const int Black = D3DCOLOR_ARGB(255, 1, 1, 1);
    const int Blue = D3DCOLOR_ARGB(255, 0, 0, 255);
    const int Red = D3DCOLOR_ARGB(255, 255, 000, 000);
    const int White = D3DCOLOR_ARGB(255, 255, 255, 255);
    const int Orange = D3DCOLOR_ARGB(255, 255, 125, 000);
    const int Yellow = D3DCOLOR_ARGB(255, 255, 255, 000);
}





#endif
