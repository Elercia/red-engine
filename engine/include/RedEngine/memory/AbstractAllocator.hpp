#pragma once
#include <cstddef>

namespace red
{
class Engine;

class AbstractAllocator
{
public:
    AbstractAllocator() = default;
    virtual ~AbstractAllocator() = default;

    virtual void* Allocate(std::size_t size) = 0;
    virtual void Free(void* ptr) = 0;
};
}  // namespace red
