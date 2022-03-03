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

    void FinalizeResource(std::shared_ptr<SpriteResource> resource);
    bool InitResource(std::shared_ptr<SpriteResource>& resource, const Path& path, nlohmann::json jsonContent);
};

}  // namespace red