#pragma once

#include "RedEngine/Utils/Types.hpp"

namespace red
{
void InitRandomEngine(uint64 seed);

uint32 RandomUint32();
uint64 RandomUint64();
}  // namespace red
