#include "RedEngine/Audio/Resource/SoundResourceLoader.hpp"

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

std::shared_ptr<SoundResource> SoundResourceLoader::LoadResource(const Path& path)
{
    namespace fs = std::filesystem;
    using json = nlohmann::json;

    auto soundResource = GetOrCreateFromCache(path);

    if (soundResource->GetLoadState() == LoadState::STATE_LOADED)
        return soundResource;

    if (!path.Exist() || path.IsDirectory())
    {
        RED_LOG_WARNING("Cannot load sound for path {}", path.GetAscciiPath());
        soundResource->SetLoadState(LoadState::STATE_ERROR);
        return soundResource;
    }

    auto parsedJson = json::parse(ReadFile(path), nullptr, false);

    if (parsedJson.is_discarded() || !parsedJson.is_object())
    {
        RED_LOG_WARNING("Path {} is not a valid JSON", path.GetAscciiPath());
        soundResource->SetLoadState(LoadState::STATE_ERROR);
        return soundResource;
    }

    auto* fmodSystem = m_world->GetSystem<AudioSystem>()->GetFmodSystem();

    std::string soundPath = parsedJson["sound_path"];
    if (soundPath.empty())
    {
        soundResource->SetLoadState(LoadState::STATE_ERROR);
        return soundResource;
    }

    FMOD::Sound* fmodSound;

    FmodUtils::FmodCheck(fmodSystem->createSound(soundPath.c_str(), FMOD_2D, nullptr, &fmodSound),
                         "Error creating sound");

    soundResource->SetSound(fmodSound);
    soundResource->SetLoadState(LoadState::STATE_LOADED);

    return soundResource;
}


void SoundResourceLoader::FreeResource(std::shared_ptr<SoundResource> resource)
{
    resource->SetLoadState(LoadState::STATE_RELEASED);
    FmodUtils::FmodCheck(resource->GetSound()->release(), "Error releasing sound");
}

}  // namespace red