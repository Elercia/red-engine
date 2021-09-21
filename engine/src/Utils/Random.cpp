#include "RedEngine/Utils/Random.hpp"

#include <random>

static std::random_device rd;
static std::mt19937_64 gen(rd());

namespace red
{
void InitRandomEngine(uint64 seed)
{
    gen.seed(seed);
}

uint32 RandomUint32()
{
    return (uint32) gen();
}

uint64 RandomUint64()
{
    return gen();
}
}  // namespace red
