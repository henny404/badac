#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include <Windows.h>
#include <functional>

namespace window
{
    extern HINSTANCE ghInstance;
    extern HWND ghWnd;
    extern wchar_t gAppName[128];
    extern wchar_t gExtendedAppName[128];
    extern std::function<void(void)> gUpdateWindowPosFunc;

    LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    bool Create(HINSTANCE hInstance, const uint32_t windowWidth, const uint32_t windowHeight);
    void Destroy();
    bool Tick();

    void SetTitle();

    namespace util
    {
        void ShowWindow(HWND hWnd);
        void CenterWindow(HWND hWnd);
    }
}

