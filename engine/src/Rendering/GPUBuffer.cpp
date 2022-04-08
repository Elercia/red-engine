#include "RedEngine/Rendering/GPUBuffer.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include <GL/gl3w.h>

namespace red
{

GPUBuffer::GPUBuffer(uint32 nbElements, uint32 elementSize) : m_nbElements(nbElements), m_elementSize(elementSize)
{
}

GPUBuffer::~GPUBuffer()
{
}

void GPUBuffer::Init()
{
    glCreateBuffers(1, &m_gpuBufferHandle);
    glNamedBufferData(m_gpuBufferHandle, m_elementSize * m_nbElements, nullptr, GL_DYNAMIC_DRAW);
}

void GPUBuffer::Finalize()
{
    glDeleteBuffers(1, &m_gpuBufferHandle);
}

void* GPUBuffer::MapData(MapType mapType)
{
    if (mappedData != nullptr)
        return mappedData;

    static const uint32 MapTypeToGlMap[] = {
        GL_READ_ONLY,   // READ
        GL_WRITE_ONLY,  // WRITE
        GL_READ_WRITE,  // READ_WRITE
    };

    uint32 glMap = MapTypeToGlMap[(int) mapType];

    void* ptr = glMapNamedBuffer(m_gpuBufferHandle, glMap);

    mappedData = ptr;

    return mappedData;
}

void GPUBuffer::UnMap()
{
    glUnmapNamedBuffer(m_gpuBufferHandle);

    mappedData = nullptr;
}

}  // namespace red
