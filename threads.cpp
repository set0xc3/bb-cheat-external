#include "threads.h"
#include "Windows.h"
#include <QDebug>

#include "mem.h"
#include "toolshack.h"
#include "blockpost.h"
#include "maths_functions.h";
#include <Psapi.h>
#include <QFontDatabase>
#include <string>

static Blockpost* _blockpost = nullptr;
static Threads* threads = nullptr;
static bool isBlockpost = true;
static int type = 0;

//static RECT rc;
//static INT SCREEN_WIDTH = 800;
//static INT SCREEN_HEIGHT = 600;

//const MARGINS margin = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };


Threads::Threads(Blockpost* block)
{
    _blockpost = block;
}

void Threads::run()
{
    threads = this;
    DirectxFunctions::ThreadProc(); // Draw
}

directx_t DirectX;

//ID3DXFont* pFont;
//LPD3DXFONT font_interface = NULL;
//IDirect3D9Ex* p_Object = 0;
//IDirect3DDevice9Ex* p_Device = 0;
//D3DPRESENT_PARAMETERS p_Params;
//RECT rc;



DWORD FrameCnt;
float TimeElapsed;
float FPS;
float oldTime;
float newTime;
float deltatime;

void CalcFPS()
{
    static DWORD LastTime = timeGetTime();

    FrameCnt++;
    TimeElapsed += timeGetTime() - LastTime;
    LastTime = timeGetTime();
    if(TimeElapsed >= 66.6666f)
    {
        FPS = 1000*(float)FrameCnt / TimeElapsed;
        TimeElapsed = 0.0f;
        FrameCnt = 0;
    }
}

//С вертикальной синхронизации
//DirectX.Param.PresentationInterval  = D3DPRESENT_INTERVAL_ONE;
//DirectX.Param.MultiSampleQuality = D3DSWAPEFFECT_COPY;

//Без вертикальной синхронизации
//DirectX.Param.PresentationInterval  = D3DPRESENT_INTERVAL_IMMEDIATE;
//DirectX.Param.SwapEffect = D3DSWAPEFFECT_DISCARD;



void DirectxFunctions::DirectXInit(HWND hwnd)
{
    if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &DirectX.Object)))
        exit(1);

    ZeroMemory(&DirectX.Param, sizeof(DirectX.Param));
    DirectX.Param.Windowed = true;
    DirectX.Param.PresentationInterval  = D3DPRESENT_INTERVAL_IMMEDIATE;
    DirectX.Param.SwapEffect = D3DSWAPEFFECT_DISCARD;
    DirectX.Param.BackBufferFormat = D3DFMT_A8R8G8B8;
    DirectX.Param.BackBufferHeight = Overlay.Height;
    DirectX.Param.BackBufferWidth = Overlay.Width;
    DirectX.Param.EnableAutoDepthStencil = true;
    DirectX.Param.AutoDepthStencilFormat = D3DFMT_D16;
    DirectX.Param.MultiSampleQuality = D3DMULTISAMPLE_NONE;


    if (FAILED(DirectX.Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &DirectX.Param, 0, &DirectX.Device)))
        exit(1);

    int id = QFontDatabase::addApplicationFont(":/resource/fonts/smallest_pixel-7.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    string sfont = family.toUtf8().constData();
    LPSTR smallest_pixel_7 = const_cast<char *>(sfont.c_str());


    D3DXCreateFont(DirectX.Device, 20, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &DirectX.Font);
    D3DXCreateFont(DirectX.Device, 10, 0, 0, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, smallest_pixel_7, &DirectX.espFont);

    if (!DirectX.Line)
        D3DXCreateLine(DirectX.Device, &DirectX.Line);
}

char textbuffer[256];// поправка: надо число в квадр. скобках обязательно
char buffer[256] ;

static bool bHandle = true;
static bool bbaseAddress = true;

struct PachFunctions
{
    bool isNoRecoil = true;
    bool isAutomaticWeapon = true;
    bool isFreezing = true;
    bool isInfiniteAmmo = true;
    bool isUnhookCamera = true;
};
PachFunctions pachFun[2];

void DirectxFunctions::RenderDirectX()
{
    if (isBlockpost  == false)
    {
        DirectX.Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
        DirectX.Device->BeginScene();


        if (threads->isActive == true){

        if (Target.Window == nullptr || threads->switchGame == true)
        {
            bHandle = true;
            bbaseAddress = true;
            threads->switchGame = false;
        }


        if (ToolsHack::GetAppstat(nullptr, "BLOCKPOST") == 1 && GetForegroundWindow() == Target.Window)
        {
            sprintf(textbuffer, "[FPS: %d]", (int)threads->m_fps );
            Drawing::String(Overlay.Width >> 1, 10, (char*)textbuffer, Color::White);

        if (threads->isActive == true && Target.Window != nullptr) //&& GetForegroundWindow() == Target.Window
        {
            _blockpost->pID = pid;
            _blockpost->pHandle = pHandle;

            //BLOCKPOST
            {
//                threads->section[threads->typeGame].weaponSetting.isRangeShovels = true;


                if (bHandle == true)
                {
//                    Threads::msleep(500);
                    _blockpost->module.GameAssembly = ToolsHack::GetModuleBaseAddress((char*)"GameAssembly.dll", _blockpost->pID);
                    _blockpost->module.UnityPlayer = ToolsHack::GetModuleBaseAddress((char*)"UnityPlayer.dll", _blockpost->pID);
                    _blockpost->module.SteamСlient = ToolsHack::GetModuleBaseAddress((char*)"steamclient.dll", _blockpost->pID);


                    if (_blockpost->module.GameAssembly == 0)return;
                    if (_blockpost->module.UnityPlayer == 0)return;
                    if (threads->typeGame == 0 && _blockpost->module.SteamСlient != 0)return;
                    if (threads->typeGame == 1 && _blockpost->module.SteamСlient == 0)return;

                    bHandle = false;
                }

                if (bbaseAddress == true)
                {
                    if (threads->typeGame == 1) //Если это Steam
                    {
                        _blockpost->baseAddress.PLH = _blockpost->module.GameAssembly + 0xB1D0FC;
                        _blockpost->baseAddress.Controll = _blockpost->module.GameAssembly + 0xB1D08C;
                        _blockpost->baseAddress.MainManager = _blockpost->module.GameAssembly + 0xB1D16C;
                        _blockpost->baseAddress.VWIK = _blockpost->module.GameAssembly + 0xB1D1D0;
                        _blockpost->baseAddress.GUIInv = _blockpost->module.GameAssembly + 0xB1D134;
                       // _blockpost->baseAddress.Players = _blockpost->module.GameAssembly + 0xB117E4;
                        _blockpost->baseAddress.MatrixBegin = _blockpost->module.UnityPlayer + 0x1059AC0;
                    }
                    else  //Если это VK
                    {
                        _blockpost->baseAddress.PLH = _blockpost->module.GameAssembly + 0xB1D3C0;
                        _blockpost->baseAddress.Controll = _blockpost->module.GameAssembly + 0xB1D34C;
                        _blockpost->baseAddress.MainManager = _blockpost->module.GameAssembly + 0xB1D3E8;
                        _blockpost->baseAddress.VWIK = _blockpost->module.GameAssembly + 0xB1D490;
                        //_blockpost->baseAddress.Players = _blockpost->module.GameAssembly + 0x0;
                        _blockpost->baseAddress.MatrixBegin = _blockpost->module.UnityPlayer + 0x1059AC0;
                    }

                    if (threads->section[threads->typeGame].weaponSetting.isNoRecoil == true)
                    {
                        pachFun[0].isNoRecoil = true;
                        pachFun[1].isNoRecoil = true;
                    }
                    if (threads->section[threads->typeGame].weaponSetting.isAutomaticWeapon == true)
                    {
                        pachFun[0].isAutomaticWeapon = true;
                        pachFun[1].isAutomaticWeapon = true;
                    }
                    if (threads->section[threads->typeGame].miscSetting.isFreezing == true)
                    {
                        pachFun[0].isFreezing = true;
                        pachFun[1].isFreezing = true;
                    }
                    if (threads->section[threads->typeGame].weaponSetting.isInfiniteAmmo == true)
                    {
                        pachFun[0].isInfiniteAmmo = true;
                        pachFun[1].isInfiniteAmmo = true;
                    }
                    if (threads->section[threads->typeGame].miscSetting.isUnhookCamera == true)
                    {
                        pachFun[0].isUnhookCamera = true;
                        pachFun[1].isUnhookCamera = true;
                    }

                    threads->section[0].weaponSetting.isRangeShovels = true;
                    threads->section[1].weaponSetting.isRangeShovels = true;

                    bbaseAddress = false;
                }

                if (threads->typeGame == 1)
                {
                    //isNoRecoil
                    if(threads->section[threads->typeGame].weaponSetting.isNoRecoil == true)
                    {
                        if(pachFun[threads->typeGame].isNoRecoil == true)
                        {
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x7A76C0 != nullptr) mem::RetEx((BYTE*)_blockpost->module.GameAssembly + 0x7A76C0, 1, _blockpost->pHandle); //VWIK__CameraAddAngle  Убирает отдачу
                            pachFun[threads->typeGame].isNoRecoil = false;
                        }
                    }
                    else
                    {
                        if(pachFun[threads->typeGame].isNoRecoil == false)
                        {
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x7A76C0 != nullptr) mem::PatchEx((BYTE*)_blockpost->module.GameAssembly + 0x7A76C0, (BYTE*)"\x55", 1, _blockpost->pHandle); //VWIK__CameraAddAngle  Убирает отдачу
                            pachFun[threads->typeGame].isNoRecoil = true;
                        }
                    }

                    //isAutomaticWeapon
                    if(threads->section[threads->typeGame].weaponSetting.isAutomaticWeapon == true)
                    {
                        if(pachFun[threads->typeGame].isAutomaticWeapon == true){
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x71BA7F != nullptr) mem::NopEx((BYTE*)_blockpost->module.GameAssembly + 0x71BA7F, 7, _blockpost->pHandle); //Делает всё оружие авто
                            pachFun[threads->typeGame].isAutomaticWeapon = false;
                        }
                    }
                    else
                    {
                        if(pachFun[threads->typeGame].isAutomaticWeapon == false)
                        {
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x71BA7F != nullptr) mem::PatchEx((BYTE*)_blockpost->module.GameAssembly + 0x71BA7F, (BYTE*)"\xC6\x80\xBC\x00\x00\x00\x01", 7, _blockpost->pHandle); //Делает всё оружие авто
                            pachFun[threads->typeGame].isAutomaticWeapon = true;
                        }
                    }

                    //isFreezing
                    if(threads->section[threads->typeGame].miscSetting.isFreezing == true)
                    {
                        if(pachFun[threads->typeGame].isFreezing == true)
                        {
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x719EE0 != nullptr) mem::RetEx((BYTE*)_blockpost->module.GameAssembly + 0x719EE0, 1, _blockpost->pHandle); //Controll__SetFreeze  Убирает замароску
                            pachFun[threads->typeGame].isFreezing = false;
                        }
                    }
                    else
                    {
                        if(pachFun[threads->typeGame].isFreezing == false)
                        {
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x719EE0 != nullptr) mem::PatchEx((BYTE*)_blockpost->module.GameAssembly + 0x719EE0, (BYTE*)"\x55", 1, _blockpost->pHandle); //Controll__SetFreeze  Убирает замароску
                            pachFun[threads->typeGame].isFreezing = true;
                        }
                    }

                    //isInfiniteAmmo
                    if(threads->section[threads->typeGame].weaponSetting.isInfiniteAmmo == true)
                    {
                        if(pachFun[threads->typeGame].isInfiniteAmmo == true)
                        {
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x72192A != nullptr) mem::NopEx((BYTE*)_blockpost->module.GameAssembly + 0x72192A, 3, _blockpost->pHandle); //Controll__UpdateWeaponAttack-Стр639  Local Убирает минус патроны
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x5EA5F0 != nullptr) mem::RetEx((BYTE*)_blockpost->module.GameAssembly + 0x5EA5F0, 1, _blockpost->pHandle); //Client__send_attack  Send Убирает минус патроны
                            pachFun[threads->typeGame].isInfiniteAmmo = false;
                        }
                    }
                    else
                    {
                        if(pachFun[threads->typeGame].isInfiniteAmmo == false)
                        {
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x72192A != nullptr) mem::PatchEx((BYTE*)_blockpost->module.GameAssembly + 0x72192A, (BYTE*)"\xFF\x4E\x28", 3, _blockpost->pHandle); //Local Убирает минус патроны
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x5EA5F0 != nullptr) mem::PatchEx((BYTE*)_blockpost->module.GameAssembly + 0x5EA5F0, (BYTE*)"\x55", 1, _blockpost->pHandle); //Send Убирает минус патроны
                            pachFun[threads->typeGame].isInfiniteAmmo = true;
                        }
                    }

                    //isUnhookCamera
                    if(threads->section[threads->typeGame].miscSetting.isUnhookCamera == true)
                    {
                        if(pachFun[threads->typeGame].isUnhookCamera == true)
                        {
                            //VWIK__CameraAddOffset
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x7A7790 != nullptr) mem::RetEx((BYTE*)_blockpost->module.GameAssembly + 0x7A7790, 1, _blockpost->pHandle); //VWIK__CameraAddOffset. убирает отдачу при отцепление камеры

                            DWORD ptrCameraFly = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.Controll, { 0x5C, 0xE8 });
                            if ((LPCVOID)ptrCameraFly != nullptr && (LPCVOID)ptrCameraFly != (LPCVOID)0xE8)
                            {
                                _blockpost->player.fly = 1;
                                WriteProcessMemory(_blockpost->pHandle, (LPCVOID*)(ptrCameraFly), &_blockpost->player.fly, 4, nullptr);
                                pachFun[threads->typeGame].isUnhookCamera = false;
                            }

                        }
                    }
                    else
                    {
                        if(pachFun[threads->typeGame].isUnhookCamera == false)
                        {
                            //VWIK__CameraAddOffset
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x7A7790 != nullptr) mem::PatchEx((BYTE*)_blockpost->module.GameAssembly + 0x7A7790, (BYTE*)"\x55", 1, _blockpost->pHandle);//VWIK__CameraAddOffset. убирает отдачу при отцепление камеры

                            DWORD ptrCameraFly = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.Controll, { 0x5C, 0xE8 });
                            if ((LPCVOID)ptrCameraFly != nullptr && (LPCVOID)ptrCameraFly != (LPCVOID)0xE8)
                            {
                                _blockpost->player.fly = 0;
                                WriteProcessMemory(_blockpost->pHandle, (LPCVOID*)(ptrCameraFly), &_blockpost->player.fly, 4, nullptr);
                                pachFun[threads->typeGame].isUnhookCamera = true;
                            }
                        }
                    }

                    //isRangeShovels
                    if(threads->section[threads->typeGame].weaponSetting.isRangeShovels == true)
                    {
                        if((BYTE*)_blockpost->module.GameAssembly + 0x72095B != nullptr)
                        {
                            mem::PatchEx((BYTE*)_blockpost->module.GameAssembly + 0x72095B, threads->section[threads->typeGame].weaponSetting.wrangeShovels, 7, _blockpost->pHandle); //Controll$$UpdateShovelAttack
                            threads->section[threads->typeGame].weaponSetting.isRangeShovels = false;
                        }
                    }


                }
                else if (threads->typeGame == 0)
                {
                    //isNoRecoil
                    if(threads->section[threads->typeGame].weaponSetting.isNoRecoil == true)
                    {
                        if(pachFun[threads->typeGame].isNoRecoil == true)
                        {
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x68ADB0 != nullptr) mem::RetEx((BYTE*)_blockpost->module.GameAssembly + 0x68ADB0, 1, _blockpost->pHandle); //VWIK__CameraAddAngle  Убирает отдачу
                            pachFun[threads->typeGame].isNoRecoil = false;
                        }
                    }
                    else
                    {
                        if(pachFun[threads->typeGame].isNoRecoil == false)
                        {
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x68ADB0 != nullptr) mem::PatchEx((BYTE*)_blockpost->module.GameAssembly + 0x68ADB0, (BYTE*)"\x55", 1, _blockpost->pHandle); //VWIK__CameraAddAngle  Убирает отдачу
                            pachFun[threads->typeGame].isNoRecoil = true;
                        }
                    }

                    //isAutomaticWeapon
                    if(threads->section[threads->typeGame].weaponSetting.isAutomaticWeapon == true)
                    {
                        if(pachFun[threads->typeGame].isAutomaticWeapon == true)
                        {
                             if ((BYTE*)_blockpost->module.GameAssembly + 0x259B3F != nullptr) mem::NopEx((BYTE*)_blockpost->module.GameAssembly + 0x259B3F, 7, _blockpost->pHandle); //Controll__UpdateAttack Делает всё оружие авто
                            pachFun[threads->typeGame].isAutomaticWeapon = false;
                        }
                    }
                    else
                    {
                        if(pachFun[threads->typeGame].isAutomaticWeapon == false)
                        {
                             if ((BYTE*)_blockpost->module.GameAssembly + 0x259B3F != nullptr) mem::PatchEx((BYTE*)_blockpost->module.GameAssembly + 0x259B3F, (BYTE*)"\xC6\x80\xBC\x00\x00\x00\x01", 7, _blockpost->pHandle); //Делает всё оружие авто
                            pachFun[threads->typeGame].isAutomaticWeapon = true;
                        }
                    }

                    //isFreezing
                    if(threads->section[threads->typeGame].miscSetting.isFreezing == true)
                    {
                        if(pachFun[threads->typeGame].isFreezing == true)
                        {
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x257FA0 != nullptr)mem::RetEx((BYTE*)_blockpost->module.GameAssembly + 0x257FA0, 1, _blockpost->pHandle); //Controll__SetFreeze  Убирает замароску
                            pachFun[threads->typeGame].isFreezing = false;
                        }
                    }
                    else
                    {
                        if(pachFun[threads->typeGame].isFreezing == false)
                        {
                             if ((BYTE*)_blockpost->module.GameAssembly + 0x257FA0 != nullptr)mem::PatchEx((BYTE*)_blockpost->module.GameAssembly + 0x257FA0, (BYTE*)"\x55", 1, _blockpost->pHandle); //Controll__SetFreeze  Убирает замароску
                            pachFun[threads->typeGame].isFreezing = true;
                        }
                    }

                    //isInfiniteAmmo
                    if(threads->section[threads->typeGame].weaponSetting.isInfiniteAmmo == true)
                    {
                        if(pachFun[threads->typeGame].isInfiniteAmmo == true)
                        {
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x25F9E9 != nullptr)mem::NopEx((BYTE*)_blockpost->module.GameAssembly + 0x25F9E9, 3, _blockpost->pHandle); //Controll__UpdateWeaponAttack-Стр622 Local Убирает минус патроны
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x155DB0 != nullptr)mem::RetEx((BYTE*)_blockpost->module.GameAssembly + 0x155DB0, 1, _blockpost->pHandle); //Client__send_attack  Send Убирает минус патроны
                            pachFun[threads->typeGame].isInfiniteAmmo = false;
                        }
                    }
                    else
                    {
                        if(pachFun[threads->typeGame].isInfiniteAmmo == false)
                        {
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x25F9E9 != nullptr)mem::PatchEx((BYTE*)_blockpost->module.GameAssembly + 0x25F9E9, (BYTE*)"\xFF\x4E\x28", 3, _blockpost->pHandle); //Local Убирает минус патроны
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x155DB0 != nullptr)mem::PatchEx((BYTE*)_blockpost->module.GameAssembly + 0x155DB0, (BYTE*)"\x55", 1, _blockpost->pHandle); //Send Убирает минус патроны
                            pachFun[threads->typeGame].isInfiniteAmmo = true;
                        }
                    }

                    //isUnhookCamera
                    if(threads->section[threads->typeGame].miscSetting.isUnhookCamera == true)
                    {
                        if(pachFun[threads->typeGame].isUnhookCamera == true)
                        {
                            //VWIK__CameraAddOffset
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x68AE80 != nullptr) mem::RetEx((BYTE*)_blockpost->module.GameAssembly + 0x68AE80, 1, _blockpost->pHandle); //VWIK__CameraAddOffset. убирает отдачу при отцепление камеры

                            DWORD ptrCameraFly = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.Controll, { 0x5C, 0xE8 });
                            if ((LPCVOID)ptrCameraFly != nullptr && (LPCVOID)ptrCameraFly != (LPCVOID)0xE8)
                            {
                                _blockpost->player.fly = 1;
                                WriteProcessMemory(_blockpost->pHandle, (LPCVOID*)(ptrCameraFly), &_blockpost->player.fly, 4, nullptr);
                                pachFun[threads->typeGame].isUnhookCamera = false;
                            }
                        }
                    }
                    else
                    {
                        if(pachFun[threads->typeGame].isUnhookCamera == false)
                        {
                            //VWIK__CameraAddOffset
                            if ((BYTE*)_blockpost->module.GameAssembly + 0x68AE80 != nullptr) mem::PatchEx((BYTE*)_blockpost->module.GameAssembly + 0x68AE80, (BYTE*)"\x55", 1, _blockpost->pHandle);//VWIK__CameraAddOffset. убирает отдачу при отцепление камеры

                            DWORD ptrCameraFly = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.Controll, { 0x5C, 0xE8 });
                            if ((LPCVOID)ptrCameraFly != nullptr && (LPCVOID)ptrCameraFly != (LPCVOID)0xE8)
                            {
                                _blockpost->player.fly = 0;
                                WriteProcessMemory(_blockpost->pHandle, (LPCVOID*)(ptrCameraFly), &_blockpost->player.fly, 4, nullptr);
                                pachFun[threads->typeGame].isUnhookCamera = true;
                            }
                        }
                    }

                    //isRangeShovels
                    if(threads->section[threads->typeGame].weaponSetting.isRangeShovels == true)
                    {
                        if(((BYTE*)_blockpost->module.GameAssembly + 0x25E4B0) != nullptr)
                        {
                            mem::PatchEx((BYTE*)_blockpost->module.GameAssembly + 0x25E4B0, threads->section[threads->typeGame].weaponSetting.wrangeShovels, 7, _blockpost->pHandle); //Controll$$UpdateShovelAttack
                            threads->section[threads->typeGame].weaponSetting.isRangeShovels = false;
                        }
                    }

                }


                DWORD ptrMatrix = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.MatrixBegin, { 0x0, 0x8, 0xBC });
                ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(ptrMatrix), &_blockpost->matrix.viewMatrix44, 64, nullptr);
                {
                    _blockpost->matrix.viewMatrix16[0] = _blockpost->matrix.viewMatrix44[0][0], _blockpost->matrix.viewMatrix16[4] = _blockpost->matrix.viewMatrix44[1][0], _blockpost->matrix.viewMatrix16[8] = _blockpost->matrix.viewMatrix44[2][0], _blockpost->matrix.viewMatrix16[12] = _blockpost->matrix.viewMatrix44[3][0],
                    _blockpost->matrix.viewMatrix16[1] = _blockpost->matrix.viewMatrix44[0][1], _blockpost->matrix.viewMatrix16[5] = _blockpost->matrix.viewMatrix44[1][1], _blockpost->matrix.viewMatrix16[9] = _blockpost->matrix.viewMatrix44[2][1], _blockpost->matrix.viewMatrix16[13] = _blockpost->matrix.viewMatrix44[3][1],
                    _blockpost->matrix.viewMatrix16[2] = _blockpost->matrix.viewMatrix44[0][2], _blockpost->matrix.viewMatrix16[6] = _blockpost->matrix.viewMatrix44[1][2], _blockpost->matrix.viewMatrix16[10] = _blockpost->matrix.viewMatrix44[2][2], _blockpost->matrix.viewMatrix16[14] = _blockpost->matrix.viewMatrix44[3][2],
                    _blockpost->matrix.viewMatrix16[3] = _blockpost->matrix.viewMatrix44[0][3], _blockpost->matrix.viewMatrix16[7] = _blockpost->matrix.viewMatrix44[1][3], _blockpost->matrix.viewMatrix16[11] = _blockpost->matrix.viewMatrix44[2][3], _blockpost->matrix.viewMatrix16[15] = _blockpost->matrix.viewMatrix44[3][3];
                }

                DWORD ptrPlayerDeath = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.PLH, { 0x5C, 0x134, 0x148 });
                ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(ptrPlayerDeath), &_blockpost->player.death, 4, nullptr);
                if (ptrPlayerDeath  != 0x148 &&_blockpost->player.death == 5)
                    pachFun[threads->typeGame].isUnhookCamera = true;


                DWORD ptrPlayerTeam = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.Controll, { 0x5C, 0x134, 0x14 });
                ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(ptrPlayerTeam), &_blockpost->player.team, 4, nullptr);

                DWORD ptrPlayerTeamZombie = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.Controll, { 0x5C, 0x134, 0x2C });
                ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(ptrPlayerTeamZombie), &_blockpost->player.teamZombie, 4, nullptr);

                if (threads->typeGame == 1)
                {
                    DWORD ptrGamemode= ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.Controll, { 0x5C, 0x1FC });
                    ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(ptrGamemode), &_blockpost->server.gamemode, 4, nullptr);
                }
                else if (threads->typeGame == 0)
                {
                    DWORD ptrGamemode= ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.Controll, { 0x5C, 0x200 });
                    ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(ptrGamemode), &_blockpost->server.gamemode, 4, nullptr);
                }



                DWORD entityDist = 0x10;
                for (int i = 0; i < 40; i++)
                {
                        if (threads->section[threads->typeGame].espSetting.isActive == false)continue;

                        DWORD ptrBaseEntity = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist });
                        ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(ptrBaseEntity), &ptrBaseEntity, 4, nullptr);
                        if (!ptrBaseEntity)
                        {
                            _blockpost->entity[i].team = 2;
                            entityDist += 0x4;
                            continue;
                        }


                        DWORD dwEntityNameDist = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x18, 0x8 });
                        ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(dwEntityNameDist), &_blockpost->entity[i].nameDist, sizeof (dwEntityNameDist), nullptr);

                        DWORD dwEntityName = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x18, 0xC });
                        ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(dwEntityName), &_blockpost->entity[i].name, _blockpost->entity[i].nameDist*4, nullptr);


                        DWORD ptrEntityVector = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x44 });
                        ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(ptrEntityVector), &_blockpost->entity[i].vector, 12, nullptr);


                        DWORD ptrEntityVectorHead = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x104, 0x8, 0x34, 0x60 });
                        ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(ptrEntityVectorHead), &_blockpost->entity[i].vectorHead, 12, nullptr);


                        _blockpost->rageShovel.distance = MathsFunctions::Distance(_blockpost->player.vector, _blockpost->entity[i].vector);


                        _blockpost->entity[i].vector.y -= 2;
                        _blockpost->entity[i].vectorHead.y += 0.5f;

                        if (_blockpost->WorldToScreen(_blockpost->entity[i].vector, _blockpost->entity[i].screen, _blockpost->matrix.viewMatrix16, Target.Size) == false)
                        {
                            entityDist += 0x4;
                            continue;
                        }

                        if (_blockpost->WorldToScreen(_blockpost->entity[i].vectorHead, _blockpost->entity[i].screenHead, _blockpost->matrix.viewMatrix16, Target.Size) == false)
                        {
                            entityDist += 0x4;
                            continue;
                        }

                        DWORD ptrEntityTeam = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x14 });
                        ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(ptrEntityTeam), &_blockpost->entity[i].team, 4, nullptr);
                        if ((LPCVOID)(ptrEntityTeam == 0x14) || _blockpost->entity[i].team == 2)
                        {
                            entityDist += 0x4;
                            continue;
                        }

                        DWORD ptrEntityTeamZombie = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x2C });
                        ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(ptrEntityTeamZombie), &_blockpost->entity[i].teamZombie, 4, nullptr);
                        if ((LPCVOID)(ptrEntityTeam == 0x2C))
                        {
                            entityDist += 0x4;
                            continue;
                        }


                        DWORD ptrIsLocalPlayer = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x1F8 });
                        ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(ptrIsLocalPlayer), &_blockpost->entity[i].isLocalPlayer, 4, nullptr);
                        if ((LPCVOID)(ptrIsLocalPlayer == 0x1F8) || _blockpost->entity[i].isLocalPlayer != NULL)
                        {
                            entityDist += 0x4;
                            continue;
                        }


                       DWORD ptrEntityHealth = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x28 });
                       ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(ptrEntityHealth), &_blockpost->entity[i].health, 4, nullptr);
                       if ((LPCVOID)(ptrEntityHealth == 0x28))
                       {
                           entityDist += 0x4;
                           continue;
                       }


                       DWORD pterEntityDeath = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x148 });
                       ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(pterEntityDeath), &_blockpost->entity[i].death, 4, nullptr);
                       if ((LPCVOID)(pterEntityDeath == 0x148) || _blockpost->entity[i].death == 5)
                       {
                           entityDist += 0x4;
                           continue;
                       }

                       DWORD pterEntityArmor = ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.PLH, { 0x5C, 0xC, entityDist, 0x198 });
                       ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(pterEntityArmor), &_blockpost->entity[i].armor, 4, nullptr);
                       if ((LPCVOID)(pterEntityDeath == 0x198))
                       {
                           entityDist += 0x4;
                           continue;
                       }

                       DWORD ptrGUIInv= ToolsHack::FindDMAAddy(_blockpost->pHandle, _blockpost->baseAddress.GUIInv, { 0x5C, 0x5C, 0xC, 0x10 });
                       ReadProcessMemory(_blockpost->pHandle, (LPCVOID)(ptrGUIInv), &_blockpost->entity[i].armor, 4, nullptr);
                       if ((LPCVOID)(ptrGUIInv == 0x10))
                       {
                           entityDist += 0x4;
                           continue;
                       }


                       if (_blockpost->server.gamemode != 2 && _blockpost->server.gamemode != 5 && _blockpost->server.gamemode != 8)
                       {
                           if(_blockpost->player.team == _blockpost->entity[i].team)
                           {
                               entityDist += 0x4;
                               continue;
                           }
                       }
                       else if (_blockpost->server.gamemode == 5)
                       {
                           if(_blockpost->player.teamZombie == _blockpost->entity[i].teamZombie)
                           {
                               entityDist += 0x4;
                               continue;
                           }
                       }

                       _blockpost->entity[i].vector.z-=0.7f;

                       if (threads->section[threads->typeGame].espSetting.is3DBox == true)
                           Drawing::Draw3DBox(_blockpost->entity[i].vectorHead, _blockpost->entity[i].vector, 0, 1,  0, _blockpost->matrix.viewMatrix16, Target.Size,
                           Drawing::QColorToD3DCOLOR(threads->section[threads->typeGame].espSetting.colorRD));


                       Drawing::Draw2DBox(_blockpost->entity[i].screenHead.x, _blockpost->entity[i].screenHead.y, _blockpost->entity[i].screen.y, threads, _blockpost, i,
                       Drawing::QColorToD3DCOLOR(threads->section[threads->typeGame].espSetting.colorRD));


                       if (threads->section[threads->typeGame].espSetting.isOutline == true)
                           Drawing::Line(Overlay.Width / 2,  Overlay.Height /  Overlay.Width, _blockpost->entity[i].screenHead.x, _blockpost->entity[i].screenHead.y,
                           Drawing::QColorToD3DCOLOR(threads->section[threads->typeGame].espSetting.colorRD));


                       if (threads->section[threads->typeGame].espSetting.isName == true)
                           Drawing::StringW(_blockpost->entity[i].screenHead.x, _blockpost->entity[i].screenHead.y, (WCHAR*)_blockpost->entity[i].name, Color::White);


//                       sprintf(buffer, "[%d]", (int)MathsFunctions::Distance(_blockpost->player.vectorHead, _blockpost->entity[i].vector));

//                       std::wstring w;
//                       std::copy(buffer, buffer + strlen(buffer), back_inserter(w));
//                       const WCHAR *pwcsDistance = w.c_str();



     //                  if (threads->section[threads->typeGame].espSetting.isDistance == true) Drawing::StringW(_blockpost->entity[i].screenHead.x, _blockpost->entity[i].screenHead.y, (WCHAR*)pwcsDistance, Color::White);


                       entityDist += 0x4;
                  }
            }
        }

//        if (_blockpost->aimBot.fov[_blockpost->aimBot.boneId] < threads->section[threads->typeGame].aimSetting.radius || _blockpost->aimBot.fov[_blockpost->aimBot.boneId] < -threads->section[threads->typeGame].aimSetting.radius) Drawing::Line(Overlay.Width / 2, Overlay.Height / 2, _blockpost->entity[_blockpost->aimBot.target].screenHead.x, _blockpost->entity[_blockpost->aimBot.target].screenHead.y, Color::White);

//        Drawing::Line(Overlay.Width / 2,  Overlay.Height / Overlay.Width, 0, 0, Color::Yellow);

        if (threads->section[threads->typeGame].aimSetting.isRadius == true)Drawing::Circle(Overlay.Width / 2, Overlay.Height / 2, (threads->section[threads->typeGame].aimSetting.radius * 11), Drawing::QColorToD3DCOLOR(threads->section[threads->typeGame].aimSetting.colorRadius));

        }
        }

        static int fps = 0;
        static float last_tick_count = 0.f;

        //Increase FPS
        fps++;

        //Get current time
        float cur_tick_count = clock( ) * 0.001f;

        //Check if the FPS haven't been updated for 1s or longer
        if ( cur_tick_count - last_tick_count >= 1.f ) {
            //Update our FPS
            last_tick_count = cur_tick_count;
            threads->m_fps = fps;
            fps = 0;
        }

        DirectX.Device->EndScene();
        DirectX.Device->PresentEx(0, 0, 0, 0, 0);



//        DirectX.Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
    }



}


MODULEINFO GetModuleInfo(char *szModule)
{
    MODULEINFO modinfo = { 0 };
    HMODULE hModule = GetModuleHandle(szModule);
    if (hModule == 0)
        return modinfo;
    GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
    return modinfo;
}


overlay_t Overlay;
target_t Target;

LRESULT CALLBACK WinProcedure(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
    case WM_PAINT:
        DirectxFunctions::RenderDirectX();
        break;

    case WM_DESTROY:
        PostQuitMessage(1);
        break;

    default:
        return DefWindowProc(hWnd, Message, wParam, lParam);
        break;
    }
    return 0;
}


/*  Возвращаемое значение:
 *  1 обычный режим приложения
 *  2 окно свёрнуто
 *  3 окно в системной области (Tray)
 * -1 окно не найдено
 */

void DirectxFunctions::ThreadProc()
{
    while (true)
    {

        //OverlayFunctions::GetTargetWindow();
        if (ToolsHack::GetAppstat(nullptr, "BLOCKPOST") == 1 && GetForegroundWindow() == Target.Window) // && GetForegroundWindow() == Target.Window
        {
            if (isBlockpost == true){
                Threads::msleep(500);
                ProcessFunctions::CheckDWM();
                OverlayFunctions::GetTargetWindow();
                OverlayFunctions::CreateClass(WinProcedure, (char*)"VC");
                OverlayFunctions::CreateWindowOverlay();
                DirectxFunctions::DirectXInit(Overlay.Window);
                isBlockpost = false;
            }

            if(threads->settingSetting.isVerticalSync == false && threads->settingSetting.VerticalSync >= 1)
            {
                DirectX.Device->Release();

                ZeroMemory(&DirectX.Param, sizeof(DirectX.Param));
                DirectX.Param.Windowed = true;
                DirectX.Param.PresentationInterval  = D3DPRESENT_INTERVAL_IMMEDIATE;
                DirectX.Param.SwapEffect = D3DSWAPEFFECT_DISCARD;
                DirectX.Param.BackBufferFormat = D3DFMT_A8R8G8B8;
                DirectX.Param.BackBufferHeight = Overlay.Height;
                DirectX.Param.BackBufferWidth = Overlay.Width;
                DirectX.Param.EnableAutoDepthStencil = true;
                DirectX.Param.AutoDepthStencilFormat = D3DFMT_D16;
                DirectX.Param.MultiSampleQuality = D3DMULTISAMPLE_NONE;

                DirectX.Device->Reset(&DirectX.Param);

                threads->settingSetting.VerticalSync = 0;
            }

            if(threads->settingSetting.isVerticalSync == true && threads->settingSetting.VerticalSync >= 1)
            {
                DirectX.Device->Release();

                ZeroMemory(&DirectX.Param, sizeof(DirectX.Param));
                DirectX.Param.Windowed = true;
                DirectX.Param.PresentationInterval  = D3DPRESENT_INTERVAL_ONE;
                DirectX.Param.SwapEffect = D3DSWAPEFFECT_COPY;
                DirectX.Param.BackBufferFormat = D3DFMT_A8R8G8B8;
                DirectX.Param.BackBufferHeight = Overlay.Height;
                DirectX.Param.BackBufferWidth = Overlay.Width;
                DirectX.Param.EnableAutoDepthStencil = true;
                DirectX.Param.AutoDepthStencilFormat = D3DFMT_D16;
                DirectX.Param.MultiSampleQuality = D3DMULTISAMPLE_NONE;

                DirectX.Device->Reset(&DirectX.Param);

                threads->settingSetting.VerticalSync = 0;
            }
        }    

                if (PeekMessage(&Overlay.Message, nullptr, 0, 0, PM_REMOVE)) //Overlay.Window
                {
                    TranslateMessage(&Overlay.Message);
                    DispatchMessage(&Overlay.Message);

                    // if msg is quit, quit
                                if (Overlay.Message.message == WM_QUIT)
                                    break;
                }


                Threads::msleep(1);
    }
}

