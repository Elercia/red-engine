#pragma once

#include "RedEngine/Utils/Types.hpp"

namespace red
{
void InitRandomEngine(uint64 seed);

uint32 RandomUint32();
uint64 RandomUint64();

uint32 RandomRange(uint32 min, uint32 max);
float RandomFloatRange(float min, float max);
}  // namespace red
