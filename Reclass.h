#ifndef RECLASS_H
#define RECLASS_H

#endif // RECLASS_H

#include <Windows.h>

namespace Reclass
{
    struct Vec4
    {
        float x, y, z, w;
    };
    struct Vec3
    {
        float x, y, z;
    };
    struct Vec2
    {
        int x, y;
    };

    // Player
    class Controll;
    class PlayerData;

    class Controll
    {
    public:
        char pad_0x0000[0xE8]; //0x0000
        __int32 freefly; //0x00E8
        char pad_0x00EC[0x4C]; //0x00EC
        PlayerData* pl; //0x0138
        char pad_0x013C[0xC8]; //0x013C
        __int32 gamemode; //0x0204
        char pad_0x0208[0x238]; //0x0208

    }; //Size=0x0440
    Controll playerent;

    class PlayerData
    {
    public:
        char pad_0x0000[0x14]; //0x0000
        __int32 team; //0x0014
        char pad_0x0018[0x14]; //0x0018
        __int32 skinstate; //0x002C
        char pad_0x0030[0x118]; //0x0030
        __int32 bstate; //0x0148
        char pad_0x014C[0x38]; //0x014C

    }; //Size=0x0184

    // Entity
    class PLH;
    class String;
    class Rigidbody;
    class N0000014D;
    class N00000164;

    class PLH
    {
    public:
        char pad_0x0000[0x14]; //0x0000
        __int32 team; //0x0014
        String* namePtr; //0x0018
        char pad_0x001C[0xC]; //0x001C
        __int32 health; //0x0028
        __int32 skinstate; //0x002C
        char pad_0x0030[0x14]; //0x0030
        vec3 currPos; //0x0044
        char pad_0x0050[0xB4]; //0x0050
        Rigidbody* rbHead; //0x0104
        char pad_0x0108[0x40]; //0x0108
        __int32 bstate; //0x0148
        char pad_0x014C[0x4C]; //0x014C
        __int32 spawnprotect; //0x0198
        char pad_0x019C[0x5C]; //0x019C
        DWORD goFPSLArm; //0x01F8
        char pad_0x01FC[0x244]; //0x01FC

    }; //Size=0x0440
    PLH* entity;

    class String
    {
    public:
        char pad_0x0000[0x8]; //0x0000
        __int32 lenName; //0x0008
        wchar_t name[68]; //0x000C

    }; //Size=0x0094

    class Rigidbody
    {
    public:
        char pad_0x0000[0x8]; //0x0000
        N0000014D* N0000014B; //0x0008

    }; //Size=0x000C

    class N0000014D
    {
    public:
        char pad_0x0000[0x34]; //0x0000
        N00000164* N0000015B; //0x0034

    }; //Size=0x0038

    class N00000164
    {
    public:
        char pad_0x0000[0x60]; //0x0000
        Vec3 coords; //0x0060

    }; //Size=0x006C


}

