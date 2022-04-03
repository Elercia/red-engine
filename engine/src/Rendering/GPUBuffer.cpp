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
    glGenBuffers(1, &m_gpuBufferHandle);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_gpuBufferHandle);
    glBufferData(GL_SHADER_STORAGE_BUFFER, m_elementSize * m_nbElements, nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void GPUBuffer::Finalize()
{
}

void GPUBuffer::UnMap()
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_gpuBufferHandle);
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    mappedData = nullptr;
}

}  // namespace red
