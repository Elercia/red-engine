#include "RedEngine/Audio/Resource/SoundResourceLoader.hpp"

#include "RedEngine/Audio/AudioModule.hpp"

#include "RedEngine/Audio/AudioUtils.hpp"
#include "RedEngine/Audio/System/AudioSystem.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Resources/ResourceHolderComponent.hpp"
#include "RedEngine/Utils/FileUtils.hpp"

#include <filesystem>
#include <fmod_common.h>
#include <nlohmann/json.hpp>

namespace red
{
SoundResourceLoader::SoundResourceLoader(World* world) : ResourceLoader(ResourceType::SPRITE, world)
{
}

SoundResourceLoader::~SoundResourceLoader()
{
}

bool SoundResourceLoader::InitResource(std::shared_ptr<SoundResource>& resource, const Path& /*path*/, nlohmann::json jsonContent)
{
    auto* fmodSystem = m_world->GetSystem<AudioSystem>()->GetFmodSystem();

    std::string soundPath = jsonContent["sound_path"];
    if (soundPath.empty())
    {
        return false;
    }

    FMOD::Sound* fmodSound;

    FmodUtils::FmodCheck(fmodSystem->createSound(soundPath.c_str(), FMOD_2D, nullptr, &fmodSound),
                         "Error creating sound");

    resource->SetSound(fmodSound);

    return true;
}

void SoundResourceLoader::FinalizeResource(std::shared_ptr<SoundResource> resource)
{
    resource->SetLoadState(LoadState::STATE_RELEASED);
    FmodUtils::FmodCheck(resource->GetSound()->release(), "Error releasing sound");
}

}  // namespace red