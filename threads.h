
#define _CRT_SECURE_NO_WARNINGS

#include "overlay.h"
#include "functions.h"
#include <string>

#include "functions.h"
#include "overlay.h"
#include "drawing.h"
#include "blockpost.h"

#include <d3d9.h>
#include <d3dx9.h>


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

using namespace std;


//__________________________________________________________________



#ifndef EXAMPLETHREADS_H
#define EXAMPLETHREADS_H

#include <QThread>
#include <QString>
#include <QDebug>
#include <QColor>

class Threads : public QThread
{

private:
    HWND OVERLAY_WINDOW;
    LPDIRECT3DDEVICE9 D3D9_DEVICE;
    LPD3DXFONT TEXT_FON;

public:
    explicit Threads(Blockpost* blockpost);

    void run();

    void initD3D(HWND hWnd);
    void MainRender();
    void BlockpostRender();

    Blockpost* blockpost;
    bool isActive = false;
    bool switchGame = false;
    int typeGame = -1;
    int m_fps;

    struct SettingSetting
    {
        int VerticalSync = 0;
        bool isVerticalSync = false;
    };
    SettingSetting settingSetting;

    struct Section
    {
        struct AimSetting
        {
            bool isActive = false;
            bool isRadius = false;

            int aim = 0;
            int smoothness = 0;
            int radius = 5;
            int bone = 0;

            QColor colorRadius = *new QColor(255, 255, 255);
        };
        AimSetting aimSetting;

        struct ESPSetting
        {
            bool isActive = true;
            bool isBox = false;
            bool is3DBox = true;
            bool isOutline = false;
            bool isName = true;
            bool isHealth = false;
            bool isArmor = true;
            bool isDistance = true;

            QColor colorRD = *new QColor(255, 255, 255);
        };
        ESPSetting espSetting;

        struct WeaponSetting
        {
            bool isActive = true;
            bool isInfiniteAmmo = false;
            bool isAutomaticWeapon = false;
            bool isNoRecoil = false;
            bool isRangeShovels = false;

            int rangeShovels = 3;

            BYTE* wrangeShovels;
        };
        WeaponSetting weaponSetting;

        struct MiscSetting
        {
            bool isUnhookCamera = false;
            bool isFreezing = false;
        };
        MiscSetting miscSetting;

    };
    Section section[2];

};

struct directx_t
{
    IDirect3D9Ex * Object;
    IDirect3DDevice9Ex * Device;
    D3DPRESENT_PARAMETERS Param;
    ID3DXFont * Font;
    ID3DXFont * espFont;
    ID3DXFont * FontWarning;
    ID3DXLine * Line;
};

extern directx_t DirectX;

namespace DirectxFunctions
{
    void DirectXInit(HWND hwnd);
    void RenderDirectX();
    void ThreadProc();
}

#endif // EXAMPLETHREADS_H
