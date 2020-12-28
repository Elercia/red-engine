#pragma once

#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Rendering/Resource/SpriteResource.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

namespace red
{
class SpriteResourceLoader : public ResourceLoader<SpriteResource>
{
public:
    SpriteResourceLoader();
    ~SpriteResourceLoader();

    std::shared_ptr<SpriteResource> LoadResource(const std::string& name);
};

}  // namespace red