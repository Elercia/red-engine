#pragma once

#include <RedEngine/memory/AbstractAllocator.hpp>

namespace red
{
class PoolAllocator : public AbstractAllocator
{
public:
    PoolAllocator(void* basePtr, std::size_t size, std::size_t blockSize);
    virtual ~PoolAllocator();

    void* Allocate(std::size_t size) override;
    void Free(void* ptr) override;

private:
    std::size_t m_blockSize;
};
} // namespace red
