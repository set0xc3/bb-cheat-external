#include "drawing.h"
#include "blockpost.h"

#define M_PI 3.141f

int GetHeightInPixels(LPD3DXFONT Font)
{
    TEXTMETRICA txtmet;
    Font->GetTextMetrics(&txtmet);
    return  txtmet.tmHeight;
}

int GetLengthInPixels(LPCSTR TextToDraw, LPD3DXFONT Font)
{
    TEXTMETRICA txtmet;

    Font->GetTextMetrics(&txtmet);

    int size = 0;

    for (int i = 0; TextToDraw[i] != '\0'; i++){
        size++;
    }

    return size * (txtmet.tmAveCharWidth + 1);
}

void GetTextSizeW(WCHAR* text, int& width, int& height)
{
    RECT Rect = { 0, 0, 0, 0 };

    DirectX.espFont->DrawTextW(nullptr, text, -1, &Rect, DT_CALCRECT, Color::White);

    width = Rect.right - Rect.left;
    height = Rect.bottom - Rect.top;
}

void GetTextSize(char* text, int& width, int& height)
{
    RECT Rect = { 0, 0, 0, 0 };

    DirectX.espFont->DrawText(nullptr, text, -1, &Rect, DT_CALCRECT, Color::White);

    width = Rect.right - Rect.left;
    height = Rect.bottom - Rect.top;
}

D3DXCOLOR Drawing::FromHSB(float hue, float saturation, float brightness)
{
    float h = hue == 1.0f ? 0 : hue * 6.0f;
    float f = h - (int)h;
    float p = brightness * (1.0f - saturation);
    float q = brightness * (1.0f - saturation * f);
    float t = brightness * (1.0f - (saturation * (1.0f - f)));
    if (h < 1)
    {
        return D3DCOLOR_XRGB((unsigned char)(brightness * 255), (unsigned char)(t * 255), (unsigned char)(p * 255));
    }
    else if (h < 2)
    {
        return D3DCOLOR_XRGB((unsigned char)(q * 255), (unsigned char)(brightness * 255), (unsigned char)(p * 255));
    }
    else if (h < 3)
    {
        return D3DCOLOR_XRGB((unsigned char)(p * 255), (unsigned char)(brightness * 255), (unsigned char)(t * 255));
    }
    else if (h < 4)
    {
        return D3DCOLOR_XRGB((unsigned char)(p * 255), (unsigned char)(q * 255), (unsigned char)(brightness * 255));
    }
    else if (h < 5)
    {
        return D3DCOLOR_XRGB((unsigned char)(t * 255), (unsigned char)(p * 255), (unsigned char)(brightness * 255));
    }
    else
    {
        return D3DCOLOR_XRGB((unsigned char)(brightness * 255), (unsigned char)(p * 255), (unsigned char)(q * 255));
    }
}

void Drawing::String(int x, int y, char *string, D3DCOLOR color)
{
    char buffer[1024] = { NULL };

    va_list args;
//    __crt_va_start_a(args, string);

    wvsprintf(buffer, string, args);
    va_end(args);

    int w = 0, h = 0;

    GetTextSize(buffer, w, h);

    x -= w / 2;

    RECT Position;
    Position.left = x;
    Position.top = y;

    DirectX.Font->DrawText(nullptr, buffer, strlen(buffer), &Position, DT_NOCLIP, color);
}

void Drawing::StringW(int x, int y, WCHAR * string, D3DCOLOR color)
{
    WCHAR buffer[1024] = { NULL };

    va_list args;
//    __crt_va_start_a(args, string);
    wvsprintfW(buffer, string, args);
    __crt_va_end(args);

    int w = 0, h = 0;

    GetTextSizeW(buffer, w, h);

    x -= w / 2;

    RECT Position;
    Position.left = x+1;
    Position.top = y-h+1;
    DirectX.espFont->DrawTextW(nullptr, buffer, lstrlenW(buffer), &Position, DT_NOCLIP, Color::Black);
    Position.left = x;
    Position.top = y-h;
    DirectX.espFont->DrawTextW(nullptr, buffer, lstrlenW(buffer), &Position, DT_NOCLIP, color);
}

void Drawing::Rect(int x, int y, int width, int height, D3DCOLOR color)
{
    D3DXVECTOR2 Rect[5];
    Rect[0] = D3DXVECTOR2(x, y);
    Rect[1] = D3DXVECTOR2(x + width, y);
    Rect[2] = D3DXVECTOR2(x + width, y + height);
    Rect[3] = D3DXVECTOR2(x, y + height);
    Rect[4] = D3DXVECTOR2(x, y);
    DirectX.Line->SetAntialias(false);
    DirectX.Line->SetWidth(1);
    DirectX.Line->Draw(Rect, 5, color);
}

void Drawing::BorderedRect(int x, int y, int width, int height, D3DCOLOR colorFill, D3DCOLOR color)
{
    D3DXVECTOR2 Fill[2];
    Fill[0] = D3DXVECTOR2(x + width / 2, y);
    Fill[1] = D3DXVECTOR2(x + width / 2, y + height);
    DirectX.Line->SetWidth(width);
    DirectX.Line->Draw(Fill, 2, colorFill);

    D3DXVECTOR2 Rect[5];
    Rect[0] = D3DXVECTOR2(x, y);
    Rect[1] = D3DXVECTOR2(x + width, y);
    Rect[2] = D3DXVECTOR2(x + width, y + height);
    Rect[3] = D3DXVECTOR2(x, y + height);
    Rect[4] = D3DXVECTOR2(x, y);
    DirectX.Line->SetAntialias(false);
    DirectX.Line->SetWidth(1);
    DirectX.Line->Draw(Rect, 5, color);
}

void Drawing::Line(int x, int y, int x2, int y2, D3DCOLOR color)
{
    D3DXVECTOR2 Line[2];
    Line[0] = D3DXVECTOR2(x, y);
    Line[1] = D3DXVECTOR2(x2, y2);
    DirectX.Line->Begin();
    DirectX.Line->SetAntialias(false);
    DirectX.Line->SetWidth(1);
    DirectX.Line->Draw(Line, 2, color);
    DirectX.Line->End();
}

void Drawing::FilledRect(int x, int y, int width, int height, D3DCOLOR color)
{
    D3DXVECTOR2 Rect[2];
    Rect[0] = D3DXVECTOR2(x + width / 2, y);
    Rect[1] = D3DXVECTOR2(x + width / 2, y + height);
    DirectX.Line->SetAntialias(false);
    DirectX.Line->SetWidth(width);
    DirectX.Line->Draw(Rect, 2, color);
}

void Drawing::Circle(int x, int y, int radius, D3DCOLOR color)
{
    D3DXVECTOR2 DotPoints[128];
    D3DXVECTOR2 Line[128];
    int Points = 0;
    for (float i = 0; i < M_PI * 2.0f; i += 0.1f)
    {
        float PointOriginX = x + radius * cos(i);
        float PointOriginY = y + radius * sin(i);
        float PointOriginX2 = radius * cos(i + 0.1) + x;
        float PointOriginY2 = radius * sin(i + 0.1) + y;
        DotPoints[Points] = D3DXVECTOR2(PointOriginX, PointOriginY);
        DotPoints[Points + 1] = D3DXVECTOR2(PointOriginX2, PointOriginY2);
        Points += 2;
    }
    DirectX.Line->Draw(DotPoints, Points, color);
    DirectX.Line->SetAntialias(false);
}

void Drawing::FilledLineBox(int x1, int y1, int x2, int y2, D3DCOLOR colorFill)
{
    FLOAT boxHeight = abs(y1 - y2);
    FLOAT boxWidth = boxHeight / 3;// boxHeight / 3;

    D3DXVECTOR2 Fill[2];
    Fill[0] = D3DXVECTOR2(x1 + boxWidth / 2, y1);
    Fill[1] = D3DXVECTOR2(x1 + boxWidth / 2, y1 + boxHeight);
    DirectX.Line->SetWidth(boxWidth);
    DirectX.Line->Draw(Fill, 2, colorFill);

    D3DXVECTOR2 Fill2[2];
    Fill2[0] = D3DXVECTOR2(x1 + boxWidth / 2, y1+2);
    Fill2[1] = D3DXVECTOR2(x1 + boxWidth / 2, y1 + (boxHeight-2));
    DirectX.Line->SetWidth(boxWidth-5);
    DirectX.Line->Draw(Fill2, 2, D3DCOLOR_ARGB(255, 0, 0, 0));

    D3DXVECTOR2 Rect[5];
    Rect[0] = D3DXVECTOR2(x1, y1);
    Rect[1] = D3DXVECTOR2(x1 + boxWidth, y1);
    Rect[2] = D3DXVECTOR2(x1 + boxWidth, y1 + boxHeight);
    Rect[3] = D3DXVECTOR2(x1, y1 + boxHeight);
    Rect[4] = D3DXVECTOR2(x1, y1);
    DirectX.Line->SetWidth(1);
    DirectX.Line->Draw(Rect, 5, D3DCOLOR_ARGB(255, 1, 1, 1));


    D3DXVECTOR2 Rect2[5];
    Rect2[0] = D3DXVECTOR2(x1+2, y1+2);
    Rect2[1] = D3DXVECTOR2(x1+ boxWidth-2, y1+2);
    Rect2[2] = D3DXVECTOR2(x1+ boxWidth-2, y1 + boxHeight-2);
    Rect2[3] = D3DXVECTOR2(x1+2, y1 + boxHeight-2);
    Rect2[4] = D3DXVECTOR2(x1+2, y1+2);
    DirectX.Line->SetWidth(1);
    DirectX.Line->Draw(Rect2, 5, D3DCOLOR_ARGB(255, 1, 1, 1));
    DirectX.Line->SetAntialias(false);
}

void Drawing::Draw2DBox(int x1, int y1, int y2, Threads *threads, Blockpost *blockpost, int i, D3DCOLOR color)
{
//        FLOAT box = abs(y1 - y2);
//        if(box < 0)
//            box *= -1;

//        int BoxWidth = box / 2;
//        int DrawX	 = x1 - (BoxWidth / 2);
//        int DrawY = y1;

//        Drawing::Rect(DrawX, DrawY, BoxWidth, box, color);



//        int boxHeight = abs(y1 - y2);
//        int boxWidth = boxHeight / 3;// boxHeight / 3;


//        int width = boxWidth;//(y2 + 15 - y1) / 4.5f
//        int height = boxHeight;//(y2 + 15 - y1) / 4.5f
//        int width2 = 1.0f;
//        int width4 = -1.0f;

//        int alpha = 255;

         // - это UP
         // + это DOWN

        // - это LEFT
        // + это RIGHT


//        Drawing::Line((x1 - width), y1, (x1 + width), y1, color); //Up
//        Drawing::Line((x1 - width), y1, (x1 -  width), (y1+height), color); //Left

//        Drawing::Line((x1 + width), y1, (x1 + width), (y1 + height), color); //Right
//        Drawing::Line((x1 - width), (y1 + height), (x1 + width)+1, (y1 + height), color); //Down


//        Drawing::Line(x1 - (width+width2)-2, (y1-width2), x1 + (width+width2)+1, (y1-width2), D3DCOLOR_ARGB(alpha, 1, 0, 0)); //Up
//        Drawing::Line(x1 - (width+width2), y1, x1 - (width+width2), y1+ (height+width2), D3DCOLOR_ARGB(alpha, 1, 0, 0)); //Left

//        //HP
//        Drawing::DrawHealthBar(x1 - (width+width2)-1, y1, (y1 / y1+ (height + width2))-1, health);

//        //Drawing::Line(x1 - (width+width2)-1, y1, x1 - (width+width2)-1, y1 + (height+width2), D3DCOLOR_ARGB(255, 0, 255, 0)); //Left
//        Drawing::Line(x1 - (width+width2)-2, y1, x1 - (width+width2)-2, y1 + (height+width2), D3DCOLOR_ARGB(alpha, 1, 0, 0)); //Left
//        //HP

//        Drawing::Line(x1 + (width+width2), y1, x1 + (width+width2), y1+ (height +width2), D3DCOLOR_ARGB(alpha, 1, 0, 0)); //Right
//        Drawing::Line(x1 - (width+width2)-2, y1+ (height +width2), x1 + (width+width2)+1, y1+ (height +width2), D3DCOLOR_ARGB(alpha, 1, 0, 0)); //Down


//        Drawing::Line(x1 - (width+width4), (y1-width4), x1 + (width+width4)+1, (y1-width4), D3DCOLOR_ARGB(alpha, 1, 0, 0)); //Up
//        Drawing::Line(x1 - (width+width4), (y1-width4), x1 - (width+width4), y1+(height-width4)-1, D3DCOLOR_ARGB(alpha, 1, 0, 0)); //Left

//        Drawing::Line(x1 + (width+width4),( y1-width4), x1 + (width+width4), y1+(height-width4)-1, D3DCOLOR_ARGB(alpha, 1, 0, 0)); //Right
//        Drawing::Line(x1 - (width+width4), y1+ (height +width4), x1 + (width+width4), y1+ (height +width4), D3DCOLOR_ARGB(alpha, 1, 0, 0)); //Down




    FLOAT box = abs(y1 - y2);
    if (box < 0)
        box *= -1;

    int BoxWidth = (box) / 2;
    int DrawX = x1 - (BoxWidth / 2);
    int DrawY = y1;
//    Drawing::Rect(DrawX-1, DrawY-1, BoxWidth+2, box+2, Color::Black); //Outside
//    Drawing::Rect(DrawX+1, DrawY+1, BoxWidth-2, box-2, Color::Black); //Inside
    if (threads->section[threads->typeGame].espSetting.isBox == true) Drawing::Rect(DrawX, DrawY, BoxWidth, box, color); //Center

    //Health
    if (threads->section[threads->typeGame].espSetting.isHealth == true)
    {
        Drawing::Rect(DrawX-4, DrawY, 2, box, Color::Black); //Outside
        Drawing::FilledRect(DrawX-4, DrawY, 2, box, D3DCOLOR_ARGB(140, 80, 80, 80)); //Inside
        Drawing::DrawHealthBar(DrawX-3, DrawY+1, (DrawY / DrawY) + (box-3), blockpost->entity[i].health, false);
    }

    if (threads->section[threads->typeGame].espSetting.isArmor == true && blockpost->entity[i].armor == true)
    {
//        Drawing::Rect(DrawX+(BoxWidth+2), DrawY, 2, box, Color::Black); //Outside
//        Drawing::FilledRect(DrawX+(BoxWidth+2), DrawY, 2, box, D3DCOLOR_ARGB(140, 80, 80, 80)); //Inside
//        Drawing::DrawHealthBar(DrawX+(BoxWidth+3), DrawY+1, (DrawY / DrawY) + (box-3), blockpost->entity[i].health, blockpost->entity[i].armor);
    }

//    Drawing::String(DrawX+5, DrawY+(DrawY / DrawY) + (box-1), (WCHAR*)L"HACK", color);
}


Blockpost  *blockpost = new Blockpost();
void Drawing::Draw3DBox(D3DXVECTOR3 top, D3DXVECTOR3 bot, int a, int width, int height, float viewMatrix[16], const RECT m_Recr, D3DCOLOR color)
{
    float box = ABS(top.y - bot.y);

    float z3D = 1.4f;

    D3DXVECTOR3 b1, b2, b3, b4, t1, t2, t3, t4;
    b1.z = b2.z = b3.z = b4.z = bot.z;


    b1.x = bot.x + (cos(TORAD(a + 45)) * width);
    b1.y = bot.y + (sin(TORAD(a + 45)) * height)+box;

    b2.x = bot.x + (cos(TORAD(a + 135)) * width);
    b2.y = bot.y + (sin(TORAD(a + 135)) * height)+box;

    b3.x = bot.x + (cos(TORAD(a + 225)) * width);
    b3.y = bot.y + (sin(TORAD(a + 225)) * height);

    b4.x = bot.x + (cos(TORAD(a + 315)) * width);
    b4.y = bot.y + (sin(TORAD(a + 315)) * height);

    t1.x = b1.x;
    t1.y = b1.y;
    t1.z = b1.z + z3D;

    t2.x = b2.x;
    t2.y = b2.y;
    t2.z = b2.z + z3D;

    t3.x = b3.x;
    t3.y = b3.y;
    t3.z = b3.z + z3D;

    t4.x = b4.x;
    t4.y = b4.y;
    t4.z = b4.z + z3D;

    D3DXVECTOR3 b1_2, b2_2, b3_2, b4_2, t1_2, t2_2, t3_2, t4_2;
    if (blockpost->WorldToScreen(b1, b1_2, viewMatrix, m_Recr) && blockpost->WorldToScreen(b2, b2_2, viewMatrix, m_Recr) && blockpost->WorldToScreen(b3, b3_2, viewMatrix, m_Recr) && blockpost->WorldToScreen(b4, b4_2, viewMatrix, m_Recr) && blockpost->WorldToScreen(t1, t1_2, viewMatrix, m_Recr) && blockpost->WorldToScreen(t2, t2_2, viewMatrix, m_Recr) && blockpost->WorldToScreen(t3, t3_2, viewMatrix, m_Recr) && blockpost->WorldToScreen(t4, t4_2, viewMatrix, m_Recr)) {

        // col
        Drawing::Line(t1_2.x, t1_2.y, b1_2.x, b1_2.y, color);
        Drawing::Line(t2_2.x, t2_2.y, b2_2.x, b2_2.y, color);
        Drawing::Line(t3_2.x, t3_2.y, b3_2.x, b3_2.y, color);
        Drawing::Line(t4_2.x, t4_2.y, b4_2.x, b4_2.y, color);

//        // top base
        Drawing::Line(t1_2.x, t1_2.y, t2_2.x, t2_2.y, color);
        Drawing::Line(t2_2.x, t2_2.y,t3_2.x, t3_2.y, color);
        Drawing::Line(t3_2.x, t3_2.y, t4_2.x, t4_2.y, color);
        Drawing::Line(t4_2.x, t4_2.y, t1_2.x, t1_2.y, color);

//        // bottom base
        Drawing::Line(b1_2.x, b1_2.y, b2_2.x, b2_2.y, color);
        Drawing::Line(b2_2.x, b2_2.y, b3_2.x, b3_2.y, color);
        Drawing::Line(b3_2.x, b3_2.y, b4_2.x, b4_2.y, color);
        Drawing::Line(b4_2.x, b4_2.y, b1_2.x, b1_2.y, color);
    }





//        D3DXVECTOR3 bounds = *new D3DXVECTOR3(5, 5, 5);
//        D3DXVECTOR3 top1 = blockpost->WorldToScreen(D3DXVECTOR3(pos.x + bounds.x, pos.y + bounds.y, pos.z + bounds.z), viewMatrix, m_Recr);
//        D3DXVECTOR3 top2 = blockpost->WorldToScreen(D3DXVECTOR3(pos.x - bounds.x, pos.y + bounds.y, pos.z + bounds.z), viewMatrix, m_Recr);
//        D3DXVECTOR3 top4 = blockpost->WorldToScreen(D3DXVECTOR3(pos.x + bounds.x, pos.y - bounds.y, pos.z + bounds.z), viewMatrix, m_Recr);
//        D3DXVECTOR3 top3 = blockpost->WorldToScreen(D3DXVECTOR3(pos.x - bounds.x, pos.y - bounds.y, pos.z + bounds.z), viewMatrix, m_Recr);
//        D3DXVECTOR3 bot1 = blockpost->WorldToScreen(D3DXVECTOR3(pos.x + bounds.x, pos.y + bounds.y, pos.z - bounds.z), viewMatrix, m_Recr);
//        D3DXVECTOR3 bot2 = blockpost->WorldToScreen(D3DXVECTOR3(pos.x - bounds.x, pos.y + bounds.y, pos.z - bounds.z), viewMatrix, m_Recr);
//        D3DXVECTOR3 bot4 = blockpost->WorldToScreen(D3DXVECTOR3(pos.x + bounds.x, pos.y - bounds.y, pos.z - bounds.z), viewMatrix, m_Recr);
//        D3DXVECTOR3 bot3 = blockpost->WorldToScreen(D3DXVECTOR3(pos.x - bounds.x, pos.y - bounds.y, pos.z - bounds.z), viewMatrix, m_Recr);

//        std::list<std::pair<D3DXVECTOR3, D3DXVECTOR3>> topLines = { { top1,top2 } };
//        std::list<std::pair<D3DXVECTOR3, D3DXVECTOR3>> botLines = { { bot1,bot2 },{ bot2,bot3 },{ bot3,bot4 },{ bot4,bot1 } };
//        std::list<std::pair<D3DXVECTOR3, D3DXVECTOR3>> sideLines = { { top1,bot1 },{ top2,bot2 },{ top3,bot3 },{ top4,bot4 } };
//        for (auto p : topLines)
//            Drawing::Line(p.first.x, p.first.y, p.second.x, p.second.y, D3DCOLOR_ARGB(255, 160, 32, 240));
//        for (auto p : botLines)
//            Drawing::Line(p.first.x, p.first.y, p.second.x, p.second.y, D3DCOLOR_ARGB(255, 160, 32, 240));
//        for (auto p : sideLines)
//           Drawing::Line(p.first.x, p.first.y, p.second.x, p.second.y, D3DCOLOR_ARGB(255, 160, 32, 240));

}



// Это 2d box как у прицела
//float w = 50;
//float h = 50;

//x1 -= ( w / 2 );
//y1 -= ( h / 2 );

//int le = w / 4;
//if( le > ( h / 4 ) )
//    le = ( h / 4 );


//Drawing::Line( x1, y1, x1 + le, y1, color);
//Drawing::Line( x1, y1, x1, y1 + le, color);
//Drawing::Line( x1 + w, y1, x1 + w - le, y1, color);
//Drawing::Line( x1 + w, y1, x1 + w, y1 + le, color);
//Drawing::Line( x1, y1 + h, x1, y1 + h - le, color);
//Drawing::Line( x1, y1 + h, x1 + le, y1 + h, color);
//Drawing::Line( x1 + w, y1 + h, x1 + w - le, y1 + h, color);
//Drawing::Line( x1 + w, y1 + h, x1 + w, y1 + h - le, color);

void Drawing::DrawLineBordered(int x, int y, int x2, int y2, D3DCOLOR color)
{
    Drawing::Line(x+1.0f, y, x2+1.0f, y2, D3DCOLOR_ARGB(255, 1, 1, 1)); //Up
    Drawing::Line(x, y, x2, y2, color); //Up
    Drawing::Line(x-1.0f, y, x2-1.0f, y2, D3DCOLOR_ARGB(255, 1, 1, 1)); //Up
}


void Drawing::DrawHealthBar(int x, int y, int height, float health, bool isArmor)
{
    float flBoxes = std::ceil( health / 10.f );
    float flX = x;
    float flY = y;
    float flHeight = height / 10.f;
    float flMultiplier = 12 / 360.f;
    flMultiplier *= flBoxes - 1;
    D3DCOLOR ColHealth = Drawing::FromHSB( flMultiplier, 1, 1 );

    //Drawing::FilledRect(flX, flY, 4, height + 2, D3DCOLOR_ARGB(125, 80, 80, 80));
    //Drawing::Rect( flX, flY, 1, height + 2, Color::Black);
   Drawing::FilledRect(flX, flY, 1, flHeight * flBoxes + 1, ColHealth );
//   if (isArmor == true) Drawing::FilledRect(flX, flY, 1, height+1, Color::Blue );
}



D3DXCOLOR Drawing::QColorToD3DCOLOR(QColor qcolor)
{
    D3DXCOLOR xcolor;
    xcolor.a = 255;
    xcolor.r =  qcolor.red();
    xcolor.g = qcolor.green();
    xcolor.b = qcolor.blue();

    return D3DCOLOR_ARGB(255, (int)xcolor.r, (int)xcolor.g, (int)xcolor.b);
}
