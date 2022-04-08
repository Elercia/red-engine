
namespace red
{
template <typename T>
T* GPUBuffer::Map(MapType mapType)
{
    return (T*)MapData(mapType);
}
}  // namespace red