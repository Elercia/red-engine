#include "RedEngine/Rendering/RenderingModule.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"

#include "RedEngine/Core/Engine.hpp"

namespace red
{
Texture2D::Texture2D(const Path& resourceId) : IResource(resourceId, ResourceType::TEXTURE2D), m_textureHandle(0)
{
}

Vector2i Texture2D::GetTextureSize() const
{
    return m_size;
}
}  // namespace red