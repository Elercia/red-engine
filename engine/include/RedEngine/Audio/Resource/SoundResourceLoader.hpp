#pragma once

#include "RedEngine/Audio/Resource/SoundResource.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

namespace red
{
class world;

class SoundResourceLoader : public ResourceLoader<SoundResource>
{
public:
    SoundResourceLoader(World* world);
    ~SoundResourceLoader();

    void FinalizeResource(std::shared_ptr<SoundResource> resource);
    bool InitResource(std::shared_ptr<SoundResource>& resource, const Path& path, nlohmann::json jsonContent);
};

}  // namespace red