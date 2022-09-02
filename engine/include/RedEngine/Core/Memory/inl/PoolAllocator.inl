
namespace red
{
template <typename T, typename... Args>
T* VirtualPoolAllocator::Allocate(Args&&... args)
{
    void* ptr = AllocateElement();

    return new (ptr) T(args...);
}

template <typename T>
void VirtualPoolAllocator::Free(T* ptr)
{
    ptr->~T();

    FreeElement((void*) ptr);
}
}  // namespace red