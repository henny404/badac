#pragma once

#include "canvas.h"
#include "Renderer/Public/IRendererDDraw.h"

using namespace yebuk::renderer;

typedef void(__cdecl* CreateInstanceFunc)(void**);

class App final
{
public:
    App() = default;
    App(const App&) = delete;
    App& operator=(const App&) = delete;
    App(App&&) = default;
    App& operator=(App&&) = default;
    ~App();

    bool Initailize(const HWND hWnd);
    void Shutdown();
    void Tick();

    inline bool IsRunning() const;

    inline bool IsUpdateFPS() const;
    inline uint32_t GetFPS() const;

    inline void UpdateWindowPos();
    inline void UpdateWindowSize();

    void ToCanvasCoord(int32_t screenX, int32_t screenY, int32_t* outCanvasX, int32_t* outCanvasY);

private:
    bool loadDLLs();
    void unloadDLLs();

    void update(const float deltaTime);
    void draw();

// Canvas 관련 함수
private:
    void drawCanvas();

private:
    static constexpr uint32_t FRAME = 60;
    static constexpr float TICKS_PER_FRAME = 1000.0f / (float)FRAME;

// DLL
private:
    HINSTANCE mhRendererDLL = nullptr;
    CreateInstanceFunc mRendererInstanceFunc = nullptr;
    IRendererDDraw* mRenderer = nullptr;

    HWND mhWnd = nullptr;

// Frame
private:
    bool mbRunning = true;

    uint32_t mFrameCount = 0;
    uint32_t mFPS = 0;
    bool mbUpdateFPS = false;

// Canvas 관련 변수
private:
    static constexpr size_t CELL_SIZE = 10;

    uint32_t* mCanvas = nullptr;
    size_t mRows = 0;
    size_t mCols = 0;

    command_t mCommand = COMMAND_DRAW_PIXEL;
    uint32_t mColor = 0xff0000;
};

inline bool App::IsRunning() const
{
    return mbRunning;
}

inline bool App::IsUpdateFPS() const
{
    return mbUpdateFPS;
}

inline uint32_t App::GetFPS() const
{
    return mFPS;
}

inline void App::UpdateWindowPos()
{
    mRenderer->UpdateWindowPos();
}

inline void App::UpdateWindowSize()
{
    mRenderer->UpdateWindowSize();
}