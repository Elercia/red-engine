#include <RedEngine/Rendering/Texture.hpp>
#include <RedEngine/Core/Engine.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>

namespace red
{
Texture::Texture(ResourceId resourceId) : Resource(resourceId, ResourceType::TEXTURE) {}

ResourceId Texture::s_nextResourceId = 0;

ResourceId Texture::GetNextResourceId() { return s_nextResourceId++; }

Texture::~Texture() { GetRedInstance().GetResourceEngine()->ReleaseTexture(this); }
SDL_Rect Texture::GetTextureSize() const { return m_textureSize; };
}  // namespace red