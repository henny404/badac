#include <cstring>

#include "Event.h"

namespace event
{
    namespace mouse
    {
        static bool sbClicked = false;
        static int32_t sClickedX;
        static int32_t sClickedY;
        static int32_t sX;
        static int32_t sY;

        void OnClick(const int32_t x, const int32_t y)
        {
            sbClicked = true;
            sClickedX = x;
            sClickedY = y;
        }

        void OnMove(const int32_t x, const int32_t y)
        {
            sX = x;
            sY = y;
        }

        bool IsClicked()
        {
            return sbClicked;
        }

        void Release()
        {
            sbClicked = false;
            sClickedX = -1;
            sClickedY = -1;
        }

        int32_t GetX()
        {
            return sX;
        }

        int32_t GetY()
        {
            return sY;
        }

        int32_t GetClickedX()
        {
            return sClickedX;
        }

        int32_t GetClickedY()
        {
            return sClickedY;
        }
    }

    namespace keyboard
    {
        static bool sbKeyMap[256] = {};

        void KeyDown(const uint8_t keyCode)
        {
            sbKeyMap[keyCode] = true;
        }

        void KeyUp(const uint8_t keyCode)
        {
            sbKeyMap[keyCode] = false;
        }

        void Release()
        {
            memset(sbKeyMap, false, sizeof(sbKeyMap));
        }

        bool IsKeyPressed(const uint8_t keyCode)
        {
            return sbKeyMap[keyCode];
        }
    }
}