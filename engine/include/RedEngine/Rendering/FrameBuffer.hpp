#pragma once

#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Utils/Types.hpp"

namespace red
{

class FrameBuffer
{
public:
    constexpr static int MaxNbColorAttachement = 4;

public:
    FrameBuffer(bool hasDepth, int nbTextures);
    ~FrameBuffer();

    bool Init(const Vector2i& size);
    void Finalize();

private:
    bool m_hasDepth;
    int m_nbTextures;

    uint32 m_iHandle;
    uint32 m_depthHandle;
    uint32 m_colorHandles[MaxNbColorAttachement];
};

}  // namespace red