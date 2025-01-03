#ifndef TOOLSHACK_H
#define TOOLSHACK_H

#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <QString>
#include <intrin.h>
#include <QCryptographicHash>

using namespace std;

namespace ToolsHack {

DWORD GetModuleBaseAddress(TCHAR* lpszModuleName, DWORD pID);
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, vector<unsigned int> offsets);

QString GetHWID();
int GetAppstat(const TCHAR* Classname, const TCHAR* Appname);

}

#endif // TOOLSHACK_H
