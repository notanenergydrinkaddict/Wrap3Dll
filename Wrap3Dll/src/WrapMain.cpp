#include <Windows.h>
#include "Memory.hpp"

DWORD Wrap3Main(void* args)
{
    const HMODULE h = GetModuleHandleW(L"Wrap.exe");
    if (h)
    {
        PatternScanVerboseConst(SelectPointPairsWrapBool_SyncViewsInit, PatternScan(h, L"31 d2 4c 89 e9 e8 ? ? ? ? b9 d0 00 00 00 e8 ? ? ? ?"));
        if (SelectPointPairsWrapBool_SyncViewsInit)
        {
            // edx is 1 already, so nop the write to 0.
            static const uint16_t nop2x = 0x9090;
            PatchBytes(SelectPointPairsWrapBool_SyncViewsInit, &nop2x, sizeof(nop2x));
        }
        PatternScanVerboseConst(SelectPointPairsSplines_SyncViewsInit, PatternScan(h, L"41 b8 01 00 00 00 31 d2 48 89 c1 48 89 c6 e8 ? ? ? ? 48 8d 15 ? ? ? ? 4c 89 e9 e8 ? ? ? ?"));
        if (SelectPointPairsSplines_SyncViewsInit)
        {
            // mov edx is shorter than r8d
            static const uint8_t p[] = { 0xBA, 0x01, 0x00, 0x00, 0x00, 0x41, 0x89, 0xD0 };
            PatchBytes(SelectPointPairsSplines_SyncViewsInit, p, sizeof(p));
        }
    }
    return 0;
}
