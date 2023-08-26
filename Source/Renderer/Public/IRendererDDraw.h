#pragma once

#ifdef RENDERER_EXPORTS
#define RENDERER_API __declspec(dllexport)
#else
#define RENDERER_API __declspec(dllimport)
#endif

#include <ddraw.h>
#include <stddef.h>
#include <stdint.h>

#include "RegionCode.h"

#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")

namespace yebuk
{
namespace renderer
{
class RENDERER_API IRendererDDraw
{
public:
    IRendererDDraw() = default;
    virtual ~IRendererDDraw() = default;

    virtual bool Initialize(const HWND hWnd) = 0;
    virtual void Cleanup() = 0;

    virtual void UpdateWindowPos() = 0;
    virtual void UpdateWindowSize() = 0;
    virtual bool CreateBackBuffer(const size_t width, const size_t height) = 0;

    virtual inline HWND GetHWnd() const = 0;
    virtual inline size_t GetWidth() const = 0;
    virtual inline size_t GetHeight() const = 0;

    virtual bool BeginDraw() = 0;
    virtual void EndDraw() = 0;
    virtual void Clear(const uint32_t color) = 0;
    virtual void OnDraw() = 0;

    virtual bool BeginGDI(HDC* outHdc) = 0;
    virtual void EndGDI(const HDC hdc) = 0;
    virtual void PrintText(const HDC hdc, const wchar_t* const text, const int32_t destX, const int32_t destY, const size_t length, const uint32_t color) = 0;

    virtual void DrawPixel(const int32_t x, const int32_t y, const uint32_t argb) = 0;
    virtual void DrawLineDDA(const int32_t startX, const int32_t startY, const int32_t endX, const int32_t endY, const uint32_t argb) = 0;
    virtual void DrawLineBresenham(const int32_t startX, const int32_t startY, const int32_t endX, const int32_t endY, const uint32_t argb) = 0;
    virtual void DrawCircle(const int32_t centerX, const int32_t centerY, const size_t radius, const uint32_t argb) = 0;
    virtual void DrawRectangle(const int32_t destX, const int32_t destY, const size_t width, const size_t height, const uint32_t argb) = 0;
    virtual void DrawBitmap(const int32_t destX, const int32_t destY, const size_t width, const size_t height, const char* const bitmap) = 0;
    virtual void DrawBitmapWithColorKey(const int32_t destX, const int32_t destY, const size_t width, const size_t height, const char* const bitmap, const uint32_t colorKey) = 0;

    virtual bool ClipLineCoham(IntVector2* inOutStartPos, IntVector2* inOutEndPos, const IntVector2& windowLeftTop, const IntVector2& windowRightBottom) = 0;
};

}
}

extern "C" RENDERER_API void __cdecl CreateInstance(void** pIRenderer);