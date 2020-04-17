#ifndef FUNCTIONS
#define FUNCTIONS

#include <Windows.h>
#include "overlay.h"
#include <time.h>

struct vec4
{
    float x, y, z, w;
};
struct vec3
{
    float x, y, z;
};
struct vec2
{
    int x, y;
};

namespace ProcessFunctions
{
    template < class TypeValue > TypeValue ReadMemory(uintptr_t Address);
    template < class TypeValue > TypeValue WriteMemory(uintptr_t Address);
    void CheckDWM();
    DWORD GetModuleBase(DWORD dwProcessIdentifier, TCHAR *lpszModuleName);
    HANDLE GetHandle();
}

template <class TypeValue>
TypeValue ProcessFunctions::ReadMemory(uintptr_t Address)
{
    TypeValue Value;
    ReadProcessMemory(pHandle, (LPCVOID*)Address, &Value, sizeof(TypeValue), 0);
    return Value;
}

template <class TypeValue>
TypeValue ProcessFunctions::WriteMemory(uintptr_t Address)
{
    TypeValue Value;
    WriteProcessMemory(pHandle, (LPCVOID*)Address, &Value, sizeof(TypeValue), 0);
    return Value;
}

#endif



