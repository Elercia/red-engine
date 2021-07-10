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

std::shared_ptr<SoundResource> SoundResourceLoader::LoadResource(const std::string& name)
{
    namespace fs = std::filesystem;
    using json = nlohmann::json;

    auto soundResource = GetOrCreateFromCache(name);

    if (soundResource->GetLoadState() == LoadState::STATE_LOADED)
        return soundResource;

    fs::path p = "RESOURCES/" + name + ".json";

    if (!fs::exists(p) || fs::is_directory(p))
    {
        RED_LOG_WARNING("Cannot load sound for path {}", p.string());
        soundResource->SetLoadState(LoadState::STATE_ERROR);
        return soundResource;
    }

    auto parsedJson = json::parse(ReadFile(p.string()), nullptr, false);

    if (parsedJson.is_discarded() || !parsedJson.is_object())
    {
        RED_LOG_WARNING("Path {} is not a valid JSON", p.string());
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

    FmodCheck(fmodSystem->createSound(soundPath.c_str(), FMOD_2D, nullptr, &fmodSound), "Error creating sound");

    soundResource->SetSound(fmodSound);
    soundResource->SetLoadState(LoadState::STATE_LOADED);

    return soundResource;
}

}  // namespace red