#pragma once

#include <RedEngine/RedEngineBase.hpp>
#include "RedEngine/Resources/Resource.hpp"
#include "RedEngine/Resources/AnnimationDescriptor.hpp"

#include <vector>

namespace red
{
class SpriteResource : IResource
{
    friend class Sprite;
    friend class SpriteResourceLoader;

public:
    RED_RESOURCE(ResourceType::SPRITE);

    SpriteResource(ResourceId resourceId);
    ~SpriteResource() = default;

private:
    std::vector<AnimationDesc> m_animations;
};
}  // namespace red