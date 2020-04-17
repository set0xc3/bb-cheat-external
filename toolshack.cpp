#include "toolshack.h"
#include <Windows.h>
#include <TlHelp32.h>
#include "QDebug"


DWORD ToolsHack::GetModuleBaseAddress(TCHAR *lpszModuleName, DWORD pID)
{
        uintptr_t modBaseAddr = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pID);
        if (hSnap != INVALID_HANDLE_VALUE)
        {
            MODULEENTRY32 modEntry;
            modEntry.dwSize = sizeof(modEntry);
            if (Module32First(hSnap, &modEntry))
            {
                do
                {
                    if (!strcmp(modEntry.szModule, lpszModuleName))
                    {
                        modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                        break;
                    }
                } while (Module32Next(hSnap, &modEntry));
            }
        }
        CloseHandle(hSnap);
        return modBaseAddr;
}

uintptr_t ToolsHack::FindDMAAddy(HANDLE hProc, uintptr_t ptr, vector<unsigned int> offsets)
{
    uintptr_t addr = ptr;
        for (unsigned int i = 0; i < offsets.size(); ++i)
        {
            ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
            addr += offsets[i];
        }
        return addr;
}

QString ToolsHack::GetHWID()
{
    TCHAR volumeName[MAX_PATH + 1] = { 0 };
    TCHAR fileSystemName[MAX_PATH + 1] = { 0 };
    DWORD serialNumber = 0;
    DWORD maxComponentLen = 0;
    DWORD fileSystemFlags = 0;
    if (GetVolumeInformation(
                nullptr,
                volumeName,
                ARRAYSIZE(volumeName),
                &serialNumber,
                &maxComponentLen,
                &fileSystemFlags,
                fileSystemName,
                ARRAYSIZE(fileSystemName)))
    {

    }


    TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName) / sizeof(computerName[0]);
    if (GetComputerName(
                computerName,
                &size))
    {

    }

    int cpuinfo[4] = { 0, 0, 0, 0 };
    __cpuid(cpuinfo, 0);
    char16_t hash = 0;
    char16_t* ptr = (char16_t*)(&cpuinfo[0]);
    for (char32_t i = 0; i < 8; i++)
        hash += ptr[i];

    QString s = computerName+QString::number(serialNumber);
    QByteArray ba = s.toUtf8();

    return QCryptographicHash::hash(ba, QCryptographicHash::Sha256).toHex();
}

int ToolsHack::GetAppstat(const TCHAR *Classname, const TCHAR *Appname)
{
    int Result = 0x0FFFFFFFF;
    HWND hWnd = FindWindow(Classname, Appname);
    if (hWnd != nullptr) {
        if (IsWindowVisible(hWnd)) {
            HWND tmp = GetLastActivePopup(hWnd);
            if (!IsIconic(tmp))
                Result = 1;
            else
                Result = 2;
        }
        else
            Result = 3;
    }
    return Result;
}
