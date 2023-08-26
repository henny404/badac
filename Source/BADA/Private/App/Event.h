#pragma once

#include <cstdint>

namespace event
{
    namespace mouse
    {
        void OnClick(const int32_t x, const int32_t y);
        void OnMove(const int32_t x, const int32_t y);
        bool IsClicked();
        void Release();
        int32_t GetX();
        int32_t GetY();
        int32_t GetClickedX();
        int32_t GetClickedY();
    }

    namespace keyboard
    {
        void KeyDown(const uint8_t keyCode);
        void KeyUp(const uint8_t keyCode);
        void Release();
        bool IsKeyPressed(const uint8_t keyCode);
    }
}