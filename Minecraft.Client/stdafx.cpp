// stdafx.cpp : source file that includes just the standard includes
// Minecraft.Client.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

#ifdef _WINDOWS64
extern HWND g_hWnd;
SceTouchData* C_4JInput::GetTouchPadData(int iPad, bool bCheckMenuDisplay) {
    static SceTouchData touchData;
    
    // 1. Reset report count
    touchData.reportNum = 0;
    touchData.timeStamp = GetTickCount64(); // Basic Windows timestamp

    // 2. Check if Left Mouse Button is held down
    bool isMouseDown = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);

    if (isMouseDown) {
        POINT p;
        if (GetCursorPos(&p)) {
            // ScreenToClient is needed if you want coordinates relative to your game window
            ScreenToClient(g_hWnd, &p);

            touchData.reportNum = 1;
            
            // PS Vita touch coordinates are typically 0-1919 for X and 0-1089 for Y
            // You may need to scale your Windows screen coordinates to match the game's expectations
            touchData.report[0].x = (unsigned short)p.x;
            touchData.report[0].y = (unsigned short)p.y;
        }
    }

    return &touchData;
}
#endif