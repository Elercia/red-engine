#include <RedEngine/Rendering/Resource/Texture2D.hpp>
#include <RedEngine/Core/Engine.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>

namespace red
{
Texture2D::Texture2D(ResourceId resourceId) : IResource(resourceId, ResourceType::TEXTURE2D) {}

Vector2i Texture2D::GetTextureSize() const { return Vector2i{m_textureSize.w, m_textureSize.h}; }

void Texture2D::ChangeTextureSize(const Vector2i& newSize)
{
    m_textureSize.w = newSize.x;
    m_textureSize.h = newSize.y;
};
}  // namespace red