#include "RedEngine/Rendering/Resource/SpriteResource.hpp"

#include "RedEngine/Resources/Resource.hpp"

namespace red
{
SpriteResource::SpriteResource(const Path& path) : IResource(path, ResourceType::SPRITE)
{
}

}  // namespace red
