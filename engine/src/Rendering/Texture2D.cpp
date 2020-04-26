#include <RedEngine/Rendering/Texture2D.hpp>
#include <RedEngine/Core/Engine.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>

namespace red
{
Texture2D::Texture2D(ResourceId_t resourceId) : Resource(resourceId, ResourceType::TEXTURE2D) {}

ResourceId_t Texture2D::s_nextResourceId = 0;

ResourceId_t Texture2D::GetNextResourceId() { return s_nextResourceId++; }

Texture2D::~Texture2D() { GetRedInstance().GetResourceEngine()->ReleaseTexture(this, true); }
SDL_Rect Texture2D::GetTextureSize() const { return m_textureSize; };
}  // namespace red