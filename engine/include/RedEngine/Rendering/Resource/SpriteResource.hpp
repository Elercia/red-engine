#pragma once

#include "RedEngine/Resources/AnnimationDescriptor.hpp"
#include "RedEngine/Resources/Resource.hpp"

#include "RedEngine/Core/Container/Array.hpp"

namespace red
{
class SpriteResource : public IResource
{
    friend class Sprite;
    friend class SpriteResourceLoader;

public:
    RED_RESOURCE(ResourceType::SPRITE, L"sprite");

    SpriteResource(const Path& path);
    ~SpriteResource() = default;

private:
    Array<AnimationDesc> m_animations;
};
}  // namespace red