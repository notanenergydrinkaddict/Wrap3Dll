#include "Memory.hpp"

#include <Windows.h>
#include <vector>

// https://github.com/OneshotGH/CSGOSimple-master/blob/master/CSGOSimple/helpers/utils.cpp
// https://github.com/illusion0001/Windows-Game-Patches/blob/0349c14b30980c8f3e3eb72532e09416516e2b5f/source/Shared/memory.cpp#L321
// Slightly modified to return pure u64

static std::vector<int> pattern_to_byte(const wchar_t* pattern)
{
    auto bytes = std::vector<int>{};
    auto start = const_cast<wchar_t*>(pattern);
    auto end = const_cast<wchar_t*>(pattern) + wcslen(pattern);

    for (auto current = start; current < end; ++current)
    {
        if (*current == L'?')
        {
            ++current;
            if (*current == L'?')
            {
                ++current;
            }
            bytes.push_back(-1);
        }
        else
        {
            bytes.push_back(wcstoul(current, &current, 16));
        }
    }
    return bytes;
}

uintptr_t PatternScan(const void* module, const wchar_t* signature)
{
    const auto dosHeader = (PIMAGE_DOS_HEADER)module;
    const auto ntHeaders = (PIMAGE_NT_HEADERS)((uint8_t*)module + dosHeader->e_lfanew);

    const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
    const auto patternBytes = pattern_to_byte(signature);
    const auto scanBytes = (uint8_t*)module;

    const auto s = patternBytes.size();
    const auto d = patternBytes.data();

    for (auto i = 0ul; i < sizeOfImage - s; ++i)
    {
        bool found = true;
        for (auto j = 0ul; j < s; ++j)
        {
            if (scanBytes[i + j] != d[j] && d[j] != -1)
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return (uintptr_t)&scanBytes[i];
        }
    }
    return 0;
}

void PatchBytes(const uintptr_t address, const void* pattern, const size_t numBytes)
{
    if (!address || !pattern || !numBytes)
    {
        return;
    }
    DWORD oldProtect{}, temp{};
    VirtualProtect((LPVOID)address, numBytes, PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy_s((LPVOID)address, numBytes, pattern, numBytes);
    VirtualProtect((LPVOID)address, numBytes, oldProtect, &temp);
}

void ShowError(const wchar_t* patternName, const wchar_t* patternExpression)
{
    wchar_t msg[2048] = { 0 };
    _snwprintf_s(msg, _countof_1(msg), L""
               "Failed to find pattern: %s\n"
               "Search expression:\n"
               "%s\n"
               "Press OK to abort pattern scan.\n"
               "(Modification for this pattern will not be applied.)", patternName, patternExpression
    );
    wprintf_s(L"MessageBox printout:\n%s\n", msg);
    MessageBox(0, msg, L"" PROJECT_NAME ". Built: " __TIME__ " @ " __DATE__, MB_ICONERROR);
}


HWND g_hConsole = 0;

void ShowConsole()
{
    AllocConsole();
    g_hConsole = GetConsoleWindow();
    if (g_hConsole)
    {
        freopen_s(reinterpret_cast<FILE**>(stdin), "conin$", "r", stdin);
        freopen_s(reinterpret_cast<FILE**>(stdout), "conout$", "w", stdout);
        freopen_s(reinterpret_cast<FILE**>(stderr), "conout$", "w", stderr);
        ShowWindow(g_hConsole, SW_SHOW);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hConsole, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hConsole, dwMode);
    }
}

void CloseConsole()
{
    if (g_hConsole)
    {
        ShowWindow(g_hConsole, SW_HIDE);
        FreeConsole();
    }
}
