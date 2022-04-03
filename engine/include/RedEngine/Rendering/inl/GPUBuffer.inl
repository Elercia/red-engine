
namespace red
{
template <typename T>
T* GPUBuffer::Map(MapType mapType)
{
    if (mappedData != nullptr)
        return (T*)mappedData;

    static const uint32 MapTypeToGlMap[] = {
        GL_READ_ONLY,   // READ
        GL_WRITE_ONLY,  // WRITE
        GL_READ_WRITE,  // READ_WRITE
    };

    uint32 glMap = MapTypeToGlMap[(int) mapType];

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_gpuBufferHandle);
    void* ptr = glMapBuffer(GL_SHADER_STORAGE_BUFFER, glMap);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    mappedData = ptr;

    return (T*) mappedData;
}
}  // namespace red