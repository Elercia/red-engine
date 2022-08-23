namespace red
{
template <typename T, typename... Args>
T* MemoryProfiler::New(int line, const char* file, Args... args)
{
    return new (Allocate(sizeof(T), line, file)) T(std::forward<Args>(args)...);
}

template <typename T>
void MemoryProfiler::Delete(T* ptr)
{
    if (ptr != nullptr)
        ptr->~T();
    Free(ptr);
}
}  // namespace red