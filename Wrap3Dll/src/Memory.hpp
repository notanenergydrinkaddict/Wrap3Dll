#include <stdint.h>
#include <stdio.h>

uintptr_t PatternScan(const void* module, const wchar_t* signature);
void PatchBytes(const uintptr_t address, const void* pattern, const size_t numBytes);
void ShowError(const wchar_t* patternName, const wchar_t* patternExpression);
void ShowConsole();
void CloseConsole();

#define PatternScanVerbose(pN, exp) uintptr_t pN = exp; printf_s("%s:%d[%s] %s = %s + 0x%p\n", __FILE__, __LINE__, __FUNCSIG__, #pN " = " #exp, PROGRAM_NAME, (void*)(pN - (uintptr_t)h)); if (!pN) { ShowError(L"" #pN, L""#exp); return 0; }
#define PatternScanVerboseConst(pN, exp) const PatternScanVerbose(pN,exp)
#define _countof_1(x) (_countof(x)-1)
