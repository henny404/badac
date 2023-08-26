#include <windowsx.h>

#include "Window.h"
#include "Event.h"

namespace window
{
    HINSTANCE ghInstance;
    HWND ghWnd;
    wchar_t gAppName[128] = L"BADA(Bit-computer Art Drawing App) - ";
    wchar_t gExtendedAppName[128] = L"";
    std::function<void(void)> gUpdateWindowPosFunc;

    LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
            break;
        }
        case WM_LBUTTONDOWN:
        {
            uint32_t x = GET_X_LPARAM(lParam);
            uint32_t y = GET_Y_LPARAM(lParam);
            event::mouse::OnClick(x, y);
            break;
        }
        case WM_MOUSEMOVE:
        {
            uint32_t x = GET_X_LPARAM(lParam);
            uint32_t y = GET_Y_LPARAM(lParam);
            event::mouse::OnMove(x, y);
            break;
        }
        case WM_MOVE:
            if (gUpdateWindowPosFunc)
            {
                gUpdateWindowPosFunc();
            }
            break;
        case WM_KEYDOWN:
            event::keyboard::KeyDown((uint8_t)wParam);
            break;
        case WM_KEYUP:
            event::keyboard::KeyUp((uint8_t)wParam);
            break;
        default:
            return DefWindowProcW(hWnd, uMsg, wParam, lParam);
        }

        return 0;
    }

    bool Create(HINSTANCE hInstance, const uint32_t windowWidth, const uint32_t windowHeight)
    {
        ghInstance = hInstance;

        WNDCLASSEXW wc = {};
        wc.cbSize = sizeof(WNDCLASSEXW);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WndProc;
        wc.hInstance = hInstance;
        wc.hIcon = nullptr;
        wc.hCursor = nullptr;
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = gAppName;
        wc.hIconSm = nullptr;

        RegisterClassExW(&wc);

        RECT windowRect = { 0, 0, (LONG)windowWidth, (LONG)windowHeight };
        AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

        static_assert(sizeof(gAppName) == sizeof(wchar_t) * 128, "Mismatch size");
        static_assert(sizeof(gExtendedAppName) == sizeof(wchar_t) * 128, "Mismatch size");
        wchar_t appName[256];

        swprintf(appName, L"%s%s", gAppName, gExtendedAppName);

        HWND hWnd = CreateWindowExW(0, gAppName, appName, WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
            CW_USEDEFAULT, CW_USEDEFAULT, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
            nullptr, nullptr, hInstance, nullptr);

        ghWnd = hWnd;
        if (ghWnd == nullptr)
        {
            return false;
        }

        return true;
    }

    void Destroy()
    {
        DestroyWindow(ghWnd);
    }

    bool Tick()
    {
        MSG msg = {};

        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);

            if (msg.message == WM_QUIT)
            {
                return false;
            }
        }

        return true;
    }

    void SetTitle()
    {
        static_assert(sizeof(gAppName) == sizeof(wchar_t) * 128, "Mismatch size");
        static_assert(sizeof(gExtendedAppName) == sizeof(wchar_t) * 128, "Mismatch size");
        wchar_t appName[256];

        swprintf(appName, L"%s%s", gAppName, gExtendedAppName);

        SetWindowTextW(ghWnd, appName);
    }

    namespace util
    {
        void ShowWindow(HWND hWnd)
        {
            ::ShowWindow(hWnd, SW_SHOW);
        }

        void CenterWindow(HWND hWnd)
        {
            const uint32_t SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
            const uint32_t SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);
            const uint32_t CENTER_SCREEN_X = SCREEN_WIDTH / 2;
            const uint32_t CENTER_SCREEN_Y = SCREEN_HEIGHT / 2;

            RECT windowRect;

            GetWindowRect(hWnd, &windowRect);
            const uint32_t WINDOW_WIDTH = windowRect.right - windowRect.left;
            const uint32_t WINDOW_HEIGHT = windowRect.bottom - windowRect.top;

            MoveWindow(hWnd, CENTER_SCREEN_X - WINDOW_WIDTH / 2, CENTER_SCREEN_Y - WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, TRUE);
        }
    }
}