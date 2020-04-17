#ifndef SIGNATURESCANNER_H
#define SIGNATURESCANNER_H

#include <iostream>
#include <string>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

class SignatureScanner
{
public:
    struct module
    {
        DWORD  Base, Size;
    };

    struct launcher
    {
        struct module
        {
            struct PLH // PLH$$Audio_fs_water
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02\x74\x14\x83\x78\x70\x00\x75\x0E\x50\xE8\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x83\xC4\x04\x8B\x40\x5C\x8B\x40\x1C\x85\xC0\x0F\x84\x00\x00\x00\x00\x3B\x70\x0C\x0F\x83";
                const char* mask = "x????xxxxxxxxxxxxxxxxx????x????xxxxxxxxxxxxx????xxxxx";
                DWORD address;
            };
            PLH PLH;

            struct VWIK // Client$$recv_detonate
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02\x74\x0F\x83\x78\x70\x00\x75\x09\x50\xE8\x00\x00\x00\x00\x83\xC4\x04\xF3\x0F\x10\x45\xF0";
                const char* mask = "x????xxxxxxxxxxxxxxxxx????xxxxxxxx";
                DWORD address;
            };
            VWIK VWIK;

            struct Controll // Controll$$AddFXAA
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02\x74\x14\x83\x78\x70\x00\x75\x0E\x50\xE8\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x83\xC4\x04\x8B\x40\x5C\x56\x8B\x70\x08\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02\x74\x0F\x83\x78\x70\x00\x75\x09\x50\xE8\x00\x00\x00\x00\x83\xC4\x04\x6A\x00\x6A\x00\x56\xE8\x00\x00\x00\x00\x83\xC4\x0C\x5E\x84\xC0\x75\x72";
                const char* mask = "x????xxxxxxxxxxxxxxxxx????x????xxxxxxxxxxx????xxxxxxxxxxxxxxxxx????xxxxxxxxx????xxxxxxxx";
                DWORD address;
            };
            Controll Controll;

            struct MainManager // MainManager$$_cctor
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\xA1\x00\x00\x00\x00\x8B\x40\x5C\xC7\x00\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x8B\x40\x5C\xC6\x40\x04\x00\xA1\x00\x00\x00\x00\x8B\x40\x5C\xC6\x40\x05\x00";
                const char* mask = "x????xxxxxxxxxx????xxxxxxxx????xxxxxxx";
                DWORD address;
            };
            MainManager MainManager;

            struct GUIInv // GUIInv$$_cctor
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\xA1\x00\x00\x00\x00\x8B\x40\x5C\xC6\x00\x00\xA1\x00\x00\x00\x00\x8B\x40\x5C\xC6\x40\x01\x00\xA1\x00\x00\x00\x00\x8B\x40\x5C\xC6\x40\x02\x00\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02";
                const char* mask = "x????xxxxxxx????xxxxxxxx????xxxxxxxx????xxxxxxx";
                DWORD address;
            };
            GUIInv GUIInv;

        };
        module module;

        struct functions
        {
            // +
            struct CameraAddAngle // VWIK$$CameraAddAngle
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\x55\x8B\xEC\x80\x3D\x00\x00\x00\x00\x00\x75\x15\xFF\x35\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04\xC6\x05\x00\x00\x00\x00\x00\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02\x74\x14\x83\x78\x70\x00\x75\x0E\x50\xE8\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x83\xC4\x04\x8B\x40\x5C\x56\x57\xFF\x35\x00\x00\x00\x00\x8B\x78\x48\xE8\x00\x00\x00\x00\xF3\x0F\x10\x45\x14\x8B\xF0\xF3\x0F\x58\x45\x18\x6A\x00\x56\xF3\x0F\x11\x45\x18\xE8\x00\x00\x00\x00\xF3\x0F\x7E\x45\x08\x83\xC4\x0C\xF3\x0F\x10\x4D\x18\x8B\x45\x10\x66\x0F\xD6\x46\x08\xF3\x0F\x10\x45\x14\xF3\x0F\x11\x4E\x24\xF3\x0F\x5C\xC8\x89\x46\x10\x8A\x45\x1C\xF3\x0F\x11\x46\x20\xC7\x46\x2C\x06\x00\x00\x00";
                const char* mask = "xxxxx?????xxxx????x????xxxxx?????x????xxxxxxxxxxxxxxxxx????x????xxxxxxxxxx????xxxx????xxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
                DWORD address;
            };
            CameraAddAngle CameraAddAngle;

            // +
            struct SetFreeze // Controll$$SetFreeze
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\x55\x8B\xEC\x51\x80\x3D\x00\x00\x00\x00\x00\x75\x15\xFF\x35\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04\xC6\x05\x00\x00\x00\x00\x00\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02\x74\x14\x83\x78\x70\x00\x75\x0E\x50\xE8\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x83\xC4\x04\x8B\x40\x5C\x56\x6A\x00\xC6\x80\x28\x01\x00\x00\x01";
                const char* mask = "xxxxxx?????xxxx????x????xxxxx?????x????xxxxxxxxxxxxxxxxx????x????xxxxxxxxxxxxxxxx";
                DWORD address;
            };
            SetFreeze SetFreeze;

             // +
            struct SendAttack // Client$$send_attack
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\x55\x8B\xEC\x80\x3D\x00\x00\x00\x00\x00\x75\x15\xFF\x35\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04\xC6\x05\x00\x00\x00\x00\x00\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02\x74\x0F\x83\x78\x70\x00\x75\x09\x50\xE8\x00\x00\x00\x00\x83\xC4\x04\x57\x6A\x00\x6A\x04";
                const char* mask = "xxxxx?????xxxx????x????xxxxx?????x????xxxxxxxxxxxxxxxxx????xxxxxxxx";
                DWORD address;
            };
            SendAttack SendAttack;

            // +
            struct CameraAddOffset // VWIK$$CameraAddOffset
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\x55\x8B\xEC\x80\x3D\x00\x00\x00\x00\x00\x75\x15\xFF\x35\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04\xC6\x05\x00\x00\x00\x00\x00\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02\x74\x14\x83\x78\x70\x00\x75\x0E\x50\xE8\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x83\xC4\x04\x8B\x40\x5C\x56\x57\xFF\x35\x00\x00\x00\x00\x8B\x78\x48\xE8\x00\x00\x00\x00\xF3\x0F\x10\x45\x14\x8B\xF0\xF3\x0F\x58\x45\x18\x6A\x00\x56\xF3\x0F\x11\x45\x18\xE8\x00\x00\x00\x00\xF3\x0F\x7E\x45\x08\x83\xC4\x0C\xF3\x0F\x10\x4D\x18\x8B\x45\x10\x66\x0F\xD6\x46\x08\xF3\x0F\x10\x45\x14\xF3\x0F\x11\x4E\x24\xF3\x0F\x5C\xC8\x89\x46\x10\x8A\x45\x1C\xF3\x0F\x11\x46\x20\xC7\x46\x2C\x04\x00\x00\x00";
                const char* mask = "xxxxx?????xxxx????x????xxxxx?????x????xxxxxxxxxxxxxxxxx????x????xxxxxxxxxx????xxxx????xxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
                DWORD address;
            };
            CameraAddOffset CameraAddOffset;

        };
        functions fun;

        struct instructions
        {
             // +
            struct AutomaticWeapon // Controll&&UpdateAttack
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\xC6\x80\xBC\x00\x00\x00\x01";
                const char* mask = "xxxxxxx";
                DWORD address;
            };
            AutomaticWeapon AutomaticWeapon;

             // +
            struct InfiniteAmmo // Controll$$UpdateWeaponAttack
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\xFF\x48\x28\x8B\x40\x28";
                const char* mask = "xxxxxx";
                DWORD address;
            };
            InfiniteAmmo InfiniteAmmo;

             // +
            struct RangeShovels // Controll$$UpdateShovelAttack
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\xC7\x04\x24\x00\x00\x40\x40\x8D\x4D\x94";
                const char* mask = "xxxxxxxxxx";
                DWORD address;
            };
            RangeShovels RangeShovels;

        };
        instructions ins;
    };
    launcher launcher;

    struct steam
    {
        struct module
        {
            struct PLH // PLH$$Audio_fs_water
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02\x74\x14\x83\x78\x70\x00\x75\x0E\x50\xE8\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x83\xC4\x04\x8B\x40\x5C\x8B\x40\x1C\x85\xC0\x0F\x84\x00\x00\x00\x00\x3B\x70\x0C\x0F\x83";
                const char* mask = "x????xxxxxxxxxxxxxxxxx????x????xxxxxxxxxxxxx????xxxxx";
                DWORD address;
            };
            PLH PLH;

            struct VWIK // Client$$recv_detonate
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02\x74\x0F\x83\x78\x70\x00\x75\x09\x50\xE8\x00\x00\x00\x00\x83\xC4\x04\xF3\x0F\x10\x45\xF0";
                const char* mask = "x????xxxxxxxxxxxxxxxxx????xxxxxxxx";
                DWORD address;
            };
            VWIK VWIK;

            struct Controll // Controll$$AddFXAA
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02\x74\x14\x83\x78\x70\x00\x75\x0E\x50\xE8\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x83\xC4\x04\x8B\x40\x5C\x56\x8B\x70\x08\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02\x74\x0F\x83\x78\x70\x00\x75\x09\x50\xE8\x00\x00\x00\x00\x83\xC4\x04\x6A\x00\x6A\x00\x56\xE8\x00\x00\x00\x00\x83\xC4\x0C\x5E\x84\xC0\x75\x72";
                const char* mask = "x????xxxxxxxxxxxxxxxxx????x????xxxxxxxxxxx????xxxxxxxxxxxxxxxxx????xxxxxxxxx????xxxxxxxx";
                DWORD address;
            };
            Controll Controll;

            struct MainManager // MainManager$$_cctor
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\xA1\x00\x00\x00\x00\x8B\x40\x5C\xC7\x00\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x8B\x40\x5C\xC6\x40\x04\x00\xA1\x00\x00\x00\x00\x8B\x40\x5C\xC6\x40\x05\x00";
                const char* mask = "x????xxxxxxxxxx????xxxxxxxx????xxxxxxx";
                DWORD address;
            };
            MainManager MainManager;

            struct GUIInv // GUIInv$$_cctor
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\xA1\x00\x00\x00\x00\x8B\x40\x5C\xC6\x00\x00\xA1\x00\x00\x00\x00\x8B\x40\x5C\xC6\x40\x01\x00\xA1\x00\x00\x00\x00\x8B\x40\x5C\xC6\x40\x02\x00\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02";
                const char* mask = "x????xxxxxxx????xxxxxxxx????xxxxxxxx????xxxxxxx";
                DWORD address;
            };
            GUIInv GUIInv;

        };
        module module;

        struct functions
        {
            // +
            struct CameraAddAngle // VWIK$$CameraAddAngle
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\x55\x8B\xEC\x80\x3D\x00\x00\x00\x00\x00\x75\x15\xFF\x35\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04\xC6\x05\x00\x00\x00\x00\x00\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02\x74\x14\x83\x78\x70\x00\x75\x0E\x50\xE8\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x83\xC4\x04\x8B\x40\x5C\x56\x57\xFF\x35\x00\x00\x00\x00\x8B\x78\x48\xE8\x00\x00\x00\x00\xF3\x0F\x10\x45\x14\x8B\xF0\xF3\x0F\x58\x45\x18\x6A\x00\x56\xF3\x0F\x11\x45\x18\xE8\x00\x00\x00\x00\xF3\x0F\x7E\x45\x08\x83\xC4\x0C\xF3\x0F\x10\x4D\x18\x8B\x45\x10\x66\x0F\xD6\x46\x08\xF3\x0F\x10\x45\x14\xF3\x0F\x11\x4E\x24\xF3\x0F\x5C\xC8\x89\x46\x10\x8A\x45\x1C\xF3\x0F\x11\x46\x20\xC7\x46\x2C\x06\x00\x00\x00";
                const char* mask = "xxxxx?????xxxx????x????xxxxx?????x????xxxxxxxxxxxxxxxxx????x????xxxxxxxxxx????xxxx????xxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
                DWORD address;
            };
            CameraAddAngle CameraAddAngle;

            // +
            struct SetFreeze // Controll$$SetFreeze
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\x55\x8B\xEC\x51\x80\x3D\x00\x00\x00\x00\x00\x75\x15\xFF\x35\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04\xC6\x05\x00\x00\x00\x00\x00\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02\x74\x14\x83\x78\x70\x00\x75\x0E\x50\xE8\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x83\xC4\x04\x8B\x40\x5C\x56\x6A\x00\xC6\x80\x28\x01\x00\x00\x01";
                const char* mask = "xxxxxx?????xxxx????x????xxxxx?????x????xxxxxxxxxxxxxxxxx????x????xxxxxxxxxxxxxxxx";
                DWORD address;
            };
            SetFreeze SetFreeze;

             // +
            struct SendAttack // Client$$send_attack
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\x55\x8B\xEC\x80\x3D\x00\x00\x00\x00\x00\x75\x15\xFF\x35\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04\xC6\x05\x00\x00\x00\x00\x00\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02\x74\x0F\x83\x78\x70\x00\x75\x09\x50\xE8\x00\x00\x00\x00\x83\xC4\x04\x57\x6A\x00\x6A\x04";
                const char* mask = "xxxxx?????xxxx????x????xxxxx?????x????xxxxxxxxxxxxxxxxx????xxxxxxxx";
                DWORD address;
            };
            SendAttack SendAttack;

            // +
            struct CameraAddOffset // VWIK$$CameraAddOffset
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\x55\x8B\xEC\x80\x3D\x00\x00\x00\x00\x00\x75\x15\xFF\x35\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04\xC6\x05\x00\x00\x00\x00\x00\xA1\x00\x00\x00\x00\xF6\x80\xBF\x00\x00\x00\x02\x74\x14\x83\x78\x70\x00\x75\x0E\x50\xE8\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x83\xC4\x04\x8B\x40\x5C\x56\x57\xFF\x35\x00\x00\x00\x00\x8B\x78\x48\xE8\x00\x00\x00\x00\xF3\x0F\x10\x45\x14\x8B\xF0\xF3\x0F\x58\x45\x18\x6A\x00\x56\xF3\x0F\x11\x45\x18\xE8\x00\x00\x00\x00\xF3\x0F\x7E\x45\x08\x83\xC4\x0C\xF3\x0F\x10\x4D\x18\x8B\x45\x10\x66\x0F\xD6\x46\x08\xF3\x0F\x10\x45\x14\xF3\x0F\x11\x4E\x24\xF3\x0F\x5C\xC8\x89\x46\x10\x8A\x45\x1C\xF3\x0F\x11\x46\x20\xC7\x46\x2C\x04\x00\x00\x00";
                const char* mask = "xxxxx?????xxxx????x????xxxxx?????x????xxxxxxxxxxxxxxxxx????x????xxxxxxxxxx????xxxx????xxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
                DWORD address;
            };
            CameraAddOffset CameraAddOffset;

        };
        functions fun;

        struct instructions
        {
            // +
            struct AutomaticWeapon // Controll&&UpdateAttack
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\xC6\x80\xBC\x00\x00\x00\x01";
                const char* mask = "xxxxxxx";
                DWORD address;
            };
            AutomaticWeapon AutomaticWeapon;

            // +
            struct InfiniteAmmo // Controll$$UpdateWeaponAttack
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\xFF\x48\x28\x8B\x40\x28";
                const char* mask = "xxxxxx";
                DWORD address;
            };
            InfiniteAmmo InfiniteAmmo;

            // +
            struct RangeShovels // Controll$$UpdateShovelAttack
            {
                const char* module = "GameAssembly.dll";
                const char* pattern = "\xC7\x04\x24\x00\x00\x40\x40\x8D\x4D\x94";
                const char* mask = "xxxxxxxxxx";
                DWORD address;
            };
            RangeShovels RangeShovels;

        };
        instructions ins;
    };
    steam steam;



    module TargetModule;
    HANDLE TargetProcess;
    DWORD TargetId;

};

namespace Scanner
{
    void Parse(char* combo, char* pattern, char* mask);
    char* ScanBasic(char* pattern, char* mask, char* begin, intptr_t size);
    char* ScanEx(char* pattern, char* mask, char* begin, intptr_t size, HANDLE hProc);
    char* ScanModEx(char* pattern, char* mask, MODULEENTRY32& modEntry, HANDLE hProc);

    DWORD GetPID(char *procName);
    DWORD GetModuleBaseAddress(DWORD pID, char *moduleName);
    DWORD GetModuleSize(DWORD pID, char *moduleName);

    BOOL ComparePattern(HANDLE pHandle, DWORD address, char *pattern, char *mask);
    DWORD ExternalAoBScan(HANDLE pHandle, DWORD pID, char *mod, char *pattern, char *mask);

};

#endif // SIGNATURESCANNER_H
