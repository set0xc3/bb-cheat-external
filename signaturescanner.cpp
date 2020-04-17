#include "signaturescanner.h"



void Scanner::Parse(char *combo, char *pattern, char *mask)
{
    char lastChar = ' ';
        unsigned int j = 0;

        for (unsigned int i = 0; i < strlen(combo); i++)
        {
            if ((combo[i] == '?' || combo[i] == '*') && (lastChar != '?' && lastChar != '*'))
            {
                pattern[j] = mask[j] = '?';
                j++;
            }

            else if (isspace(lastChar))
            {
                pattern[j] = lastChar = (char)strtol(&combo[i], 0, 16);
                mask[j] = 'x';
                j++;
            }
            lastChar = combo[i];
        }
        pattern[j] = mask[j] = '\0';
}

char *Scanner::ScanBasic(char *pattern, char *mask, char *begin, intptr_t size)
{
    intptr_t patternLen = strlen(mask);

    for (int i = 0; i < size; i++)
    {
        bool found = true;
        for (int j = 0; j < patternLen; j++)
        {
            if (mask[j] != '?' && pattern[j] != *(char*)((intptr_t)begin + i + j))
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return (begin + i);
        }
    }
    return nullptr;
}

char *Scanner::ScanEx(char *pattern, char *mask, char *begin, intptr_t size, HANDLE hProc)
{
    char* match{ nullptr };
    SIZE_T bytesRead;
    DWORD oldprotect;
    char* buffer{ nullptr };
    MEMORY_BASIC_INFORMATION mbi;
    mbi.RegionSize = 0x1000;//

    VirtualQueryEx(hProc, (LPCVOID)begin, &mbi, sizeof(mbi));

    for (char* curr = begin; curr < begin + size; curr += mbi.RegionSize)
    {
        if (!VirtualQueryEx(hProc, curr, &mbi, sizeof(mbi))) continue;
        if (mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) continue;

        delete[] buffer;
        buffer = new char[mbi.RegionSize];

        if (VirtualProtectEx(hProc, mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &oldprotect))
        {
            ReadProcessMemory(hProc, mbi.BaseAddress, buffer, mbi.RegionSize, &bytesRead);
            VirtualProtectEx(hProc, mbi.BaseAddress, mbi.RegionSize, oldprotect, &oldprotect);

            char* internalAddr = ScanBasic(pattern, mask, buffer, (intptr_t)bytesRead);

            if (internalAddr != nullptr)
            {
                //calculate from internal to external
                match = curr + (internalAddr - buffer);
                break;
            }
        }
    }
    delete[] buffer;
    return match;
}

char *Scanner::ScanModEx(char *pattern, char *mask, MODULEENTRY32 &modEntry, HANDLE hProc)
{
    return ScanEx(pattern, mask, (char*)modEntry.modBaseAddr, modEntry.modBaseSize, hProc);
}

DWORD Scanner::GetPID(char *procName)
{
    PROCESSENTRY32 entry;
        entry.dwSize = sizeof(PROCESSENTRY32);
        DWORD pID = NULL;

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);				// Creates a snapshot of the currently running processes to itterate over

        if (Process32First(snapshot, &entry)){												// Grabs the first process' information
            do {
                if (_stricmp(entry.szExeFile, procName) == 0){ 								// Compare the process file name to the only argument passed into the function
                    pID = entry.th32ProcessID;												// If they are the same set the pID value to that process pID
                    break;																	// and break out of the do while loop
                }
            } while (Process32Next(snapshot, &entry));										// Continue scanning the next process in the snapshot
        }

        CloseHandle(snapshot);																// Close the handle since we're done with it

        return pID;
}

DWORD Scanner::GetModuleBaseAddress(DWORD pID, char *moduleName)
{
    MODULEENTRY32 entry;
        entry.dwSize = sizeof(MODULEENTRY32);
        DWORD baseAddress = 0;

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);					// Creates a snapshot of the process with the provided process ID

        if (Module32First(snapshot, &entry)) {												// Grabs the first modules information
            do {
                if (_stricmp(entry.szModule, moduleName) == 0) {							// Compares the module name to the argument passed into the function
                    baseAddress = (DWORD)entry.modBaseAddr;									// if they are the same set the baseAddress variable to the base address of the module
                    break;																	// and break out of the do while loop
                }
            } while (Module32Next(snapshot, &entry));										// continue scanning the next module in the snapshot
        }

        CloseHandle(snapshot);																// Close the handle since we're done with it
        return baseAddress;
}

DWORD Scanner::GetModuleSize(DWORD pID, char *moduleName)
{
    MODULEENTRY32 entry;
        entry.dwSize = sizeof(MODULEENTRY32);
        DWORD moduleSize = 0;

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);					// Creates a snapshot of the process with the provided process ID

        if (Module32First(snapshot, &entry)) {												// Grabs the first modules information
            do {
                if (_stricmp(entry.szModule, moduleName) == 0) {							// Compares the module name to the argument passed into the function
                    moduleSize = (DWORD)entry.modBaseSize;									// if they are the same set the moduleSize variable to the size of the module
                    break;																	// and break out of the do while loop
                }
            } while (Module32Next(snapshot, &entry));										// continue scanning the next module in the snapshot
        }

        CloseHandle(snapshot);																// Close the handle since we're done with it
        return moduleSize;
}

BOOL Scanner::ComparePattern(HANDLE pHandle, DWORD address, char *pattern, char *mask)
{
    DWORD patternSize = strlen(mask);													// Set the length of the pattern so we don't scan more than we need to

        auto memBuf = new char[patternSize + 1];											// Creaet a new char array with the length of the pattern size
        memset(memBuf, 0, patternSize + 1);													// Set the above array to all 0s
        ReadProcessMemory(pHandle, (LPVOID)address, memBuf, patternSize, 0);				// Read the memory from the address provied (With a langth of the pattern size to the above array


        for (DWORD i = 1; i < patternSize; i++) {											// For each byte in the above array

            if (memBuf[i] != pattern[i] && mask[i] != *"?") {								// If the pattern at that index doesn't match the array at that index, and the mask doesn't have a wild card
                delete memBuf;																// Delete the buffer we created
                return false;																// Return false since the pattern didn't match
            }
        }
        delete memBuf;																		// Delete the buffer we created
        return true;
}

uintptr_t Scanner::ExternalAoBScan(HANDLE pHandle, uintptr_t pID, char *mod, char *pattern, char *mask)
{
        std::vector<uintptr_t> matches;																		// Create a vector to store all our results in
        uintptr_t patternSize = strlen(mask);																// Store the length of the pattern

        uintptr_t moduleBase = GetModuleBaseAddress(pID, mod);												// Get the base address of the module
        uintptr_t moduleSize = GetModuleSize(pID, mod);														// Get the size of the module

        if (!moduleBase || !moduleSize) {																// If either GetModuleBaseAddress or GetModuleSize returned NULL
            std::cout << "Could not get " << mod << " base address or size" << std::endl;				// Let the user know
            return NULL;																				// Return NULL
        }

        auto moduleBytes = new char[moduleSize + 1];													// Create a new array of bytes the size of the module
        memset(moduleBytes, 0, moduleSize + 1);															// Set all the bytes in that array to 0
        ReadProcessMemory(pHandle, (LPVOID)moduleBase, moduleBytes, moduleSize, 0);						// Read the entire module into a local buffer that we can read from

        for (int i = 0; i + patternSize < moduleSize; i++) {											// For each byte in that module, if the index + the pattern size wont go past the end of the buffer
            if (pattern[0] == moduleBytes[i]) {															// If the first byte in the pattern is equal to the current byte in the module memory
                if (ComparePattern(pHandle, moduleBase + i, pattern, mask)) {							// Check if the entire pattern matches
                    matches.push_back(moduleBase + i);													// If it does, push that address into the matches Vector
                }
            }
        }

        delete moduleBytes;																				// Delete the buffer we created

        if (matches.size() == 0) {																		// If there we no matches
            return NULL;																				// Return NULL
        }
        return matches[0];
}


