#pragma once

#include "RedEngine/Utils/Types.hpp"

#include <GL/gl3w.h>

namespace red
{
enum class MapType
{
	READ,
	WRITE,
	READ_WRITE
};

class GPUBuffer
{
    friend class Renderer;

public:
    GPUBuffer(uint32 nbElements, uint32 elementSize);
    ~GPUBuffer();

    void Init();
    void Finalize();

    template <typename T>
    T* Map(MapType mapType);
    void UnMap();

private:
    void* mappedData{nullptr};

    uint32 m_nbElements;
    uint32 m_elementSize;
    uint32 m_gpuBufferHandle;
};
}  // namespace red

#include "inl/GPUBuffer.inl"