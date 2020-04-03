#ifndef MEM_H
#define MEM_H

#include <Windows.h>

namespace mem
{
    void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
    void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);
    void RetEx(BYTE* dst, unsigned int size, HANDLE hProcess);
}

#endif // MEM_H
