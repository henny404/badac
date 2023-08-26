#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <cstdint>

#include "App.h"
#include "Window.h"
#include "Core/Public/Util/Assert.h"

App* gApp = nullptr;

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    constexpr uint32_t WINDOW_WIDTH = 800;
    constexpr uint32_t WINDOW_HEIGHT = 600;

    if (!window::Create(hInstance, WINDOW_WIDTH, WINDOW_HEIGHT))
    {
        ASSERT(false, L"Failed to Create Window");
        goto EXIT;
    }

    window::util::ShowWindow(window::ghWnd);
    window::util::CenterWindow(window::ghWnd);

    gApp = new App();
    if (!gApp->Initailize(window::ghWnd))
    {
        ASSERT(false, L"Failed to init app");
        goto EXIT;
    }

    window::gUpdateWindowPosFunc = []()
    {
        gApp->UpdateWindowPos();
    };

    while (window::Tick())
    {
        if (gApp->IsUpdateFPS())
        {
            const uint32_t fps = gApp->GetFPS();
            swprintf(window::gExtendedAppName, L"FPS: %lu", fps);
            window::SetTitle();
        }

        gApp->Tick();
    }

EXIT:
    if (gApp != nullptr)
    {
        gApp->Shutdown();
        delete gApp;
    }

    window::Destroy();

    return 0;
}