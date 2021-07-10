#pragma once

#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Rendering/Resource/SpriteResource.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

namespace red
{
class world;

class SpriteResourceLoader : public ResourceLoader<SpriteResource>
{
public:
    SpriteResourceLoader(World* world);
    ~SpriteResourceLoader();

    std::shared_ptr<SpriteResource> LoadResource(const std::string& name);

    void FreeResource(std::shared_ptr<red::SpriteResource> resource) override;
};

}  // namespace red