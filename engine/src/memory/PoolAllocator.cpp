#include <RedEngine/debug/Debug.hpp>
#include <RedEngine/memory/PoolAllocator.hpp>

namespace red
{

PoolAllocator::PoolAllocator(void* basePtr, std::size_t size, std::size_t blockSize)
    : AbstractAllocator(), m_blockSize(blockSize)
{
    RED_ASSERT(size % blockSize == 0, "The pool size must be a multiple of the block size");
}

PoolAllocator::~PoolAllocator() {}

void* PoolAllocator::Allocate(std::size_t size) { return nullptr; }

void PoolAllocator::Free(void* ptr) {}
} // namespace red
