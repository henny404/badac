#include <Windows.h>
#include <stdlib.h>

#include "App.h"
#include "Event.h"
#include "Core/Public/Util/Assert.h"
#include "Core/Public/Util/SafeDelete.h"
#include "Core/Public/Util/Timer.h"
#include "Math/Public/Color.h"

App::~App()
{
    Shutdown();
}

bool App::Initailize(const HWND hWnd)
{
    mhWnd = hWnd;

    if (!loadDLLs())
    {
        goto EXIT;
    }

    mRendererInstanceFunc((void**)&mRenderer);

    if (!mRenderer->Initialize(hWnd))
    {
        goto EXIT;
    }

    mRows = mRenderer->GetHeight() / CELL_SIZE;
    mCols = mRenderer->GetWidth() / CELL_SIZE;

    mCanvas = (uint32_t*)malloc(sizeof(uint32_t) * mRows * mCols);
    memset(mCanvas, 0xffffff, sizeof(uint32_t) * mRows * mCols);

    set_canvas(mCanvas, mRows, mCols);

    mCommand = COMMAND_DRAW_PIXEL;
    mColor = 0xff0000;

    return true;

EXIT:
    Shutdown();
    return false;
}
void App::Shutdown()
{
    unloadDLLs();
    release_canvas();
    SAFE_FREE(mCanvas);
}

void App::Tick()
{
    static yebuk::core::util::Timer gameFrameTimer(TICKS_PER_FRAME);

    gameFrameTimer.Update();
    if (gameFrameTimer.IsOnTick())
    {
        const float deltaTime = gameFrameTimer.GetDeltaTime();
        update(deltaTime);
    }

    draw();
}

void App::ToCanvasCoord(int32_t screenX, int32_t screenY, int32_t* outCanvasX, int32_t* outCanvasY)
{
    ASSERT(outCanvasX != nullptr, "outCanvasX == nullptr");
    ASSERT(outCanvasY != nullptr, "outCanvasY == nullptr");

    *outCanvasX = screenX / (int32_t)CELL_SIZE;
    *outCanvasY = screenY / (int32_t)CELL_SIZE;
}

bool App::loadDLLs()
{
    const wchar_t* rendererDLLName = nullptr;

#if defined(_DEBUG)
#if defined(_M_IX86)
    rendererDLLName = L"RendererDDraw_x86d.dll";
#elif defined(_M_X64)
    rendererDLLName = L"RendererDDraw_x64d.dll";
#endif // _M_IX86
#else
#if defined(_M_IX86)
    rendererDLLName = L"RendererDDraw_x86.dll";
#elif defined(_M_X64)
    rendererDLLName = L"RendererDDraw_x64.dll";
#endif // _M_IX86
#endif // _DEBUG

    mhRendererDLL = LoadLibrary(rendererDLLName);
    if (mhRendererDLL == nullptr)
    {
        ASSERT(false, L"Failed to Load RendererDDraw dll");
        goto EXIT;
    }

    mRendererInstanceFunc = (CreateInstanceFunc)GetProcAddress(mhRendererDLL, "CreateInstance");
    if (mRendererInstanceFunc == nullptr)
    {
        ASSERT(false, L"Failed to load CreateInstance() function");
        goto EXIT;
    }

    // 도움말 띄워주기
    event::keyboard::KeyDown(VK_F1);

    return true;

EXIT:
    unloadDLLs();
    return false;
}

void App::unloadDLLs()
{
    if (mhRendererDLL != nullptr)
    {
        mRenderer->Cleanup();
        delete mRenderer;

        FreeLibrary(mhRendererDLL);
        mhRendererDLL = nullptr;
    }
}

void App::update(const float deltaTime)
{
    static uint32_t clickCount = 0;

    if (event::keyboard::IsKeyPressed(VK_F1))
    {
        const wchar_t* text = L"\
            F1: 도움말\n\
            F2: 색상 선택\n\
            F3: 모두 지우기\n\
            F5: 되돌리기\n\
            F6: 되돌리기 취소\n\n\
            1: 픽셀 그리기\n\
            2: 지우개\n\
            3: 채우기\n\
            4: 수평선 그리기\n\
            5: 수직선 그리기\n\
            6: 사각형 그리기";
        MessageBox(nullptr, text, L"도움말", MB_OK | MB_ICONINFORMATION);
    }

    if (event::keyboard::IsKeyPressed(VK_F2))
    {
        static COLORREF customColors[16];
        uint32_t r = (mColor & 0xFF0000) >> 16;
        uint32_t g = mColor & 0xFF00;
        uint32_t b = (mColor & 0xFF) << 16;

        uint32_t defaultColor = r | g | b;

        CHOOSECOLOR cc;
        ZeroMemory(&cc, sizeof(cc));
        cc.lStructSize = sizeof(cc);
        cc.lpCustColors = (LPDWORD)customColors;
        cc.Flags = CC_FULLOPEN | CC_RGBINIT;
        cc.hwndOwner = mhWnd;
        cc.rgbResult = defaultColor;

        if (ChooseColor(&cc))
        {
            uint32_t r = (cc.rgbResult & 0xFF) << 16;
            uint32_t g = cc.rgbResult & 0xFF00;
            uint32_t b = (cc.rgbResult & 0xFF0000) >> 16;
            mColor = r | g | b;
        }
    }

    if (event::keyboard::IsKeyPressed(VK_F3))
    {
        fill_canvas(0xffffff);
    }

    if (event::keyboard::IsKeyPressed('1'))
    {
        mCommand = COMMAND_DRAW_PIXEL;
    }

    if (event::keyboard::IsKeyPressed('2'))
    {
        mCommand = COMMAND_REMOVE_PIXEL;
    }

    if (event::keyboard::IsKeyPressed('3'))
    {
        mCommand = COMMAND_FILL_CANVAS;
    }

    if (event::keyboard::IsKeyPressed('4'))
    {
        mCommand = COMMAND_DRAW_HORIZONTAL_LINE;
    }

    if (event::keyboard::IsKeyPressed('5'))
    {
        mCommand = COMMAND_DRAW_VERTICAL_LINE;
    }

    if (event::keyboard::IsKeyPressed('6'))
    {
        mCommand = COMMAND_DRAW_RECTANGLE;
    }

    if (event::keyboard::IsKeyPressed(VK_F5))
    {
        undo();
    }

    if (event::keyboard::IsKeyPressed(VK_F6))
    {
        redo();
    }
    
    if (mCommand != COMMAND_DRAW_RECTANGLE)
    {
        clickCount = 0;
    }

    if (event::mouse::IsClicked())
    {
        int32_t x;
        int32_t y;
        ToCanvasCoord(event::mouse::GetClickedX(), event::mouse::GetClickedY(), &x, &y);

        switch (mCommand)
        {
        case COMMAND_DRAW_PIXEL:
            draw_pixel(x, y, mColor);
            break;
        case COMMAND_REMOVE_PIXEL:
            remove_pixel(x, y);
            break;
        case COMMAND_FILL_CANVAS:
            fill_canvas(mColor);
            break;
        case COMMAND_DRAW_HORIZONTAL_LINE:
            draw_horizontal_line(y, mColor);
            break;
        case COMMAND_DRAW_VERTICAL_LINE:
            draw_vertical_line(x, mColor);
            break;
        case COMMAND_DRAW_RECTANGLE:
        {
            static int32_t prevClickedX;
            static int32_t prevClickedY;

            if (clickCount == 0)
            {
                prevClickedX = x;
                prevClickedY = y;

                ++clickCount;
            }
            else
            {
                int32_t startX = yebuk::math::MathUtil::Min<int32_t>(prevClickedX, x);
                int32_t startY = yebuk::math::MathUtil::Min<int32_t>(prevClickedY, y);
                int32_t endX = yebuk::math::MathUtil::Max<int32_t>(prevClickedX, x);
                int32_t endY = yebuk::math::MathUtil::Max<int32_t>(prevClickedY, y);

                draw_rectangle(startX, startY, endX, endY, mColor);

                prevClickedX = 0;
                prevClickedY = 0;

                clickCount = 0;
            }
            break;
        }
        default:
            ASSERT(false, "Invalid drawing mode");
            break;
        }

        event::mouse::Release();
    }

    event::keyboard::Release();
}

void App::draw()
{
    mRenderer->BeginDraw();
    {
        drawCanvas();
    }
    mRenderer->EndDraw();

    mRenderer->OnDraw();

    static yebuk::core::util::Timer fpsTimer(1000.0f);
    fpsTimer.Update();

    ++mFrameCount;
    if (fpsTimer.IsOnTick())
    {
        mFPS = mFrameCount;
        mFrameCount = 0;
        mbUpdateFPS = true;
    }
    else
    {
        mbUpdateFPS = false;
    }
}

void App::drawCanvas()
{
    const size_t WINDOW_WIDTH = mRenderer->GetWidth();
    const size_t WINDOW_HEIGHT = mRenderer->GetHeight();

    for (size_t r = 0; r < mRows; ++r)
    {
        const size_t y = CELL_SIZE * r + 1;
        for (size_t c = 0; c < mCols; ++c)
        {
            const size_t x = CELL_SIZE * c + 1;
            const uint32_t color = mCanvas[r * mCols + c];
            mRenderer->DrawRectangle((int32_t)x, (int32_t)y, CELL_SIZE - 2, CELL_SIZE - 2, color);
        }
    }
}