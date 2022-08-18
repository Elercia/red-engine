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
    return (uint32)RandomUint64();
}

uint64 RandomUint64()
{
    uint64 x = s_state;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;

    s_state = x;

	return x;
}
}  // namespace red
