#pragma once

#include "../Public/IRendererDDraw.h"

namespace yebuk
{
namespace renderer
{
class RendererDDraw final : public IRendererDDraw
{
public:
    RendererDDraw() = default;
    RendererDDraw(const RendererDDraw&) = delete;
    RendererDDraw& operator=(const RendererDDraw&) = delete;
    RendererDDraw(RendererDDraw&&) = delete;
    RendererDDraw& operator=(RendererDDraw&&) = delete;
    virtual ~RendererDDraw();

    virtual bool Initialize(const HWND hWnd) override;
    virtual void Cleanup() override;

    virtual void UpdateWindowPos() override;
    virtual void UpdateWindowSize() override;
    virtual bool CreateBackBuffer(const size_t width, const size_t height) override;

    virtual inline HWND GetHWnd() const override { return mhWnd; }
    virtual inline size_t GetWidth() const override { return mWidth; }
    virtual inline size_t GetHeight() const override { return mHeight; }

    virtual bool BeginDraw() override;
    virtual void EndDraw() override;
    virtual void Clear(const uint32_t color) override;
    virtual void OnDraw() override;

    virtual bool BeginGDI(HDC* outHdc) override;
    virtual void EndGDI(const HDC hdc) override;
    virtual void PrintText(const HDC hdc, const wchar_t* const text, const int32_t destX, const int32_t destY, const size_t length, const uint32_t color) override;

    virtual void DrawPixel(const int32_t x, const int32_t y, const uint32_t argb) override;
    virtual void DrawLineDDA(const int32_t startX, const int32_t startY, const int32_t endX, const int32_t endY, const uint32_t argb) override;
    virtual void DrawLineBresenham(const int32_t startX, const int32_t startY, const int32_t endX, const int32_t endY, const uint32_t argb) override;
    virtual void DrawCircle(const int32_t centerX, const int32_t centerY, const size_t radius, const uint32_t argb) override;
    virtual void DrawRectangle(const int32_t destX, const int32_t destY, const size_t width, const size_t height, const uint32_t argb) override;
    virtual void DrawBitmap(const int32_t destX, const int32_t destY, const size_t width, const size_t height, const char* const bitmap) override;
    virtual void DrawBitmapWithColorKey(const int32_t destX, const int32_t destY, const size_t width, const size_t height, const char* const bitmap, const uint32_t colorKey) override;

    virtual bool ClipLineCoham(IntVector2* inOutStartPos, IntVector2* inOutEndPos, const IntVector2& windowLeftTop, const IntVector2& windowRightBottom) override;

private:
    HWND mhWnd = 0;
    RECT mWindowRect = {};
    size_t mWidth = 0;
    size_t mHeight = 0;

    char* mLockedBackBuffer = nullptr;
    size_t mLockedBackBufferPitch = 0;

    IDirectDraw* mDD = nullptr;
    IDirectDraw7* mDD7 = nullptr;
    IDirectDrawSurface7* mPrimary = nullptr;
    IDirectDrawSurface7* mBack = nullptr;
    IDirectDrawClipper* mClipper = nullptr;
};
}
}