#include "RedEngine/Rendering/FrameBuffer.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"
#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/Renderable.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/RenderDebugUtils.hpp"
#include "RedEngine/Rendering/Resource/Material.hpp"
#include "RedEngine/Rendering/Resource/ShaderProgram.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"
#include "RedEngine/Utils/Types.hpp"

#include "GL/glcorearb.h"

namespace red
{

FrameBuffer::FrameBuffer(bool hasDepth, int nbTextures)
    : m_hasDepth(hasDepth), m_nbTextures(nbTextures), m_iHandle((uint32) -1)
{
}

FrameBuffer::~FrameBuffer()
{
    Finalize();
}

bool FrameBuffer::Init(const Vector2i& size)
{
    glCreateFramebuffers(1, &m_iHandle);

    if (m_hasDepth)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_depthHandle);
        glTextureStorage2D(m_depthHandle, 1, GL_DEPTH24_STENCIL8, size.width, size.height);
        glTextureSubImage2D(m_depthHandle, 0, 0, 0, size.width, size.height, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8,
                            nullptr);

        glNamedFramebufferTexture(m_iHandle, GL_DEPTH_ATTACHMENT, m_depthHandle, 0);
    }

    for (int i = 0; i < m_nbTextures; i++)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_colorHandles[i]);

        glTextureStorage2D(m_colorHandles[i], 1, GL_RGB8, size.width, size.height);
        glTextureSubImage2D(m_colorHandles[i], 0, 0, 0, size.width, size.height, GL_RGB, GL_UNSIGNED_INT, nullptr);

        glNamedFramebufferTexture(m_iHandle, GL_COLOR_ATTACHMENT0 + i, m_colorHandles[i], 0);
    }

    return true;
}

void FrameBuffer::Finalize()
{
    glDeleteFramebuffers(1, &m_iHandle);

	if(m_hasDepth)
		glDeleteTextures(1, &m_depthHandle);

	for (int i = 0; i < m_nbTextures; i++)
    {
		glDeleteTextures(1, &m_colorHandles[i]);
    }

}
}  // namespace red
