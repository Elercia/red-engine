#include "RedEngine/Utils/Random.hpp"

#include "RedEngine/Utils/UtilityModule.hpp"

namespace red
{
static uint64 s_state = 1;

void InitRandomEngine(uint64 seed)
{
    s_state = seed;
}

uint32 RandomUint32()
{
    return (uint32) RandomUint64();
}

// xorshift64*
uint64 RandomUint64()
{
    uint64 x = s_state;
    x ^= x >> 12;
    x ^= x << 25;
    x ^= x >> 27;

    s_state = x * 0x2545F4914F6CDD1DULL;

    return x;
}

uint32 RandomRange(uint32 min, uint32 max)
{
    const auto fRandValue = (float) RandomUint32() / (float) UINT_MAX;

    return (uint32)(fRandValue * (max-min)) + min;
}

float RandomFloatRange(float min, float max)
{
    const auto fRandValue = (float) RandomUint32() / (float) UINT_MAX;
    return ( fRandValue * (max - min)) + min;
}
}  // namespace red
