#pragma once

#ifdef TIMER_CLASS_EXPORTS
#define TIMER_CLASS_API __declspec(dllexport)
#else
#define TIMER_CLASS_API __declspec(dllimport)
#endif

#include <Windows.h>

namespace yebuk
{
namespace core
{
namespace util
{
class TIMER_CLASS_API Timer final
{
public:
    Timer(const float interval);
    Timer(const Timer&) = default;
    Timer& operator=(const Timer&) = default;
    Timer(Timer&&) = default;
    Timer& operator=(Timer&&) = default;
    virtual ~Timer() = default;

    void Update();

    inline float GetInterval() const { return mInterval; }
    inline float GetDeltaTime() const { return mElapsedTick / 1000.0f; }
    inline bool IsOnTick() const { return mbOnTick; }

private:
    float mInterval = 0.0f;
    float mElapsedTick = 0.0f;
    bool mbOnTick = false;

    LARGE_INTEGER mFrequency = {};
    LARGE_INTEGER mPrevCounter = {};
};
}
}
}