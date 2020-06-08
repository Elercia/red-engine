#include <RedEngine/Rendering/Texture2D.hpp>
#include <RedEngine/Core/Engine.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>

namespace red
{
Texture2D::Texture2D(ResourceId_t resourceId) : Resource(resourceId, ResourceType::TEXTURE2D) {}

ResourceId_t Texture2D::s_nextResourceId = 0;

ResourceId_t Texture2D::GetNextResourceId() { return s_nextResourceId++; }

Point Texture2D::GetTextureSize() const { return Point{m_textureSize.w, m_textureSize.h}; }

void Texture2D::Release() { GetRedSubEngine<ResourceEngine>()->ReleaseTexture(this, false); }

void Texture2D::ChangeTextureSize(const Point& newSize)
{
    m_textureSize.w = newSize.x;
    m_textureSize.h = newSize.y;
};
}  // namespace red