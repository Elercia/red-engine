namespace red
{
template <typename T>
T* LinearAllocator::Allocate(int count /*= 1*/)
{
    auto* ptr = Allocate(sizeof(T), count);
    if (ptr == nullptr)
        return nullptr;
    return new (ptr) T();
}
}  // namespace red