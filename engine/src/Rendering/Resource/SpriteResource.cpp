#include "RedEngine/Rendering/Resource/SpriteResource.hpp"

#include "RedEngine/Resources/Resource.hpp"

namespace red
{
SpriteResource::SpriteResource(ResourceId resourceId) : IResource(std::move(resourceId), ResourceType::SPRITE) {}

}  // namespace red
