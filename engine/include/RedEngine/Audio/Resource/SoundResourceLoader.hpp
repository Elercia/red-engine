#pragma once

#include "RedEngine/Audio/Resource/SoundResource.hpp"
#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

namespace red
{
class world;

class SoundResourceLoader : public ResourceLoader<SoundResource>
{
public:
    SoundResourceLoader(World* world);
    ~SoundResourceLoader();

    std::shared_ptr<SoundResource> LoadResource(const Path& path);

    void FreeResource(std::shared_ptr<red::SoundResource> resource) override;
};

}  // namespace red