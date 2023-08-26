#pragma once

#ifdef REGION_CODE_EXPORTS
#define REGION_CODE_API __declspec(dllexport)
#else
#define REGION_CODE_API __declspec(dllimport)
#endif

#include <stdint.h>

#include "Math/Public/IntVector2.h"

namespace yebuk
{
namespace renderer
{
using namespace yebuk::math;

REGION_CODE_API uint8_t MakeRegionCode(const IntVector2& pos, const IntVector2& regionLeftTopPos, const IntVector2& regionRightBottom);
}
}