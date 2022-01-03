#pragma once

#include "RedEngine/Resources/AnnimationDescriptor.hpp"
#include "RedEngine/Resources/Resource.hpp"

#include <vector>

namespace red
{
class SpriteResource : public IResource
{
    friend class Sprite;
    friend class SpriteResourceLoader;

public:
    RED_RESOURCE(ResourceType::SPRITE);

    SpriteResource(const Path& path);
    ~SpriteResource() = default;

private:
    std::vector<AnimationDesc> m_animations;
};
}  // namespace red