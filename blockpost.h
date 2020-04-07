#ifndef BLOCKPOST_H
#define BLOCKPOST_H

#include <Windows.h>
#include <TlHelp32.h>
#include <d3dx9math.h>

using namespace std;

class Blockpost
{
public:
    Blockpost();

    DWORD pID;
    HWND hGameWindow;
    HANDLE pHandle;


    struct Module
    {
        DWORD SteamСlient;
        DWORD UnityPlayer;
        DWORD GameAssembly;
    };
    Module module;


    struct Offsets
    {
        DWORD PLH = 0xB1D0FC;
        DWORD VWIK = 0xB1D1D0;
        DWORD Controll = 0xB1D08C;
        DWORD MainManager = 0xB1D16C;
        DWORD MatrixBegin = 0x1059AC0;
    };
    Offsets offsets;

    struct BaseAddress
    {
        DWORD PLH;
        DWORD VWIK;
        DWORD Controll;
        DWORD MainManager;
        DWORD GUIInv;
        DWORD MatrixBegin;
        DWORD Players;
    };
    BaseAddress baseAddress;


    struct Server
    {
        int players;
        int gamemode;
    };
    Server server;


    struct Player
    {
        int health;
        int team;
        int teamZombie;
        bool fly;
        DWORD death;
        D3DXVECTOR3 angle;
        D3DXVECTOR3 vector;
        D3DXVECTOR3 vectorHead;
    };
    Player player;


    struct Entity
    {
        int buffer = 0;
        int buffer2 = 0;
        int health;
        int team;
        int teamZombie;
        int nameDist;
        bool armor;
        bool isReady;
        float diffAng[12];
        WCHAR* name[68];
        DWORD isLocalPlayer;
        DWORD death;
        D3DXVECTOR3 angle[12];
        D3DXVECTOR3 vector;
        D3DXVECTOR3 vectorHead;
        D3DXVECTOR3 vectorHeadT;
        D3DXVECTOR3 vectorBody;
        D3DXVECTOR3 vectorBodyT;
        D3DXVECTOR3 vectorLArm[2];
        D3DXVECTOR3 vectorRArm[2];
        D3DXVECTOR3 vectorLLeg[3];
        D3DXVECTOR3 vectorRLeg[3];
        D3DXVECTOR3 vectorDistance;
        D3DXVECTOR3 screen;
        D3DXVECTOR3 screenHead;
        D3DXVECTOR3 screenBody;
        D3DXVECTOR3 screenLArm[2];
        D3DXVECTOR3 screenRArm[2];
        D3DXVECTOR3 screenLLeg[3];
        D3DXVECTOR3 screenRLeg[3];
        D3DXVECTOR3 screenDistance;
    };
    Entity entity[40];


    struct RageShovel
    {
        int boneId;
        int target = -1;
        bool isActive = true;
        float distance;
        float minDiffAng;
        D3DXVECTOR3 screen;
    };
    RageShovel rageShovel;


    struct AimBot
    {
        int boneId;
        int target = -1;
        bool isActive = true;
        float fov[12];
        float minDiffAng;
    };
    AimBot aimBot;


    struct Matrix
    {
        float viewMatrix44[4][4];
        float viewMatrix16[16];
    };
    Matrix matrix;


    struct GUIInv
    {
        struct Set
        {
            struct Slot
            {

            };
            Slot slot[2];
        };
        Set set[3];
    };
    GUIInv guiInv;


    bool WorldToScreen(D3DXVECTOR3 vector, D3DXVECTOR3 &screen, float viewMatrix[16], const RECT m_Rect);
    D3DXVECTOR3 WorldToScreen(D3DXVECTOR3 vector, float viewMatrix[16], const RECT m_Rect);
};


#endif // BLOCKPOST_H
