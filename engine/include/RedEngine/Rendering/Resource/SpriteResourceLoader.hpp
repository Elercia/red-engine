#pragma once

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

    std::shared_ptr<SpriteResource> LoadResource(const Path& path);

    void FreeResource(std::shared_ptr<SpriteResource> resource) override;
};

}  // namespace red