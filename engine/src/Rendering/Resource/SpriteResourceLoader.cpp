#include "RedEngine/Rendering/Resource/SpriteResourceLoader.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Utils/FileUtils.hpp"
#include "RedEngine/Resources/AnnimationDescriptor.hpp"
#include "RedEngine/Rendering/Resource/TextureResourceLoader.hpp"

#include <filesystem>
#include <nlohmann/json.hpp>

namespace red
{
SpriteResourceLoader::SpriteResourceLoader()
    : ResourceLoader("Sprite", ResourceType::SPRITE)
{
}

SpriteResourceLoader::~SpriteResourceLoader() {}

std::shared_ptr<red::SpriteResource> SpriteResourceLoader::LoadResource(const std::string& name)
{
    namespace fs = std::filesystem;
    using json = nlohmann::json;

    auto spriteResource = GetOrCreateFromCache(name);

    if (spriteResource->GetLoadState() == LoadState::STATE_LOADED)
        return spriteResource;

    fs::path p = GetRedSubEngine<Configuration>()->GetResourceFolder() + "/" + name + ".json";

    if (!fs::exists(p) || fs::is_directory(p))
    {
        RED_LOG_WARNING("Cannot load sprite for path {}", p.string());
        return nullptr;
    }

    auto parsedJson = json::parse(ReadFile(p.string()), nullptr, false);

    if (parsedJson.is_discarded() || !parsedJson.is_array())
    {
        RED_LOG_WARNING("Path {} is not a valid JSON", p.string());
        return nullptr;
    }

    auto* textureResourceLoader = GetRedSubEngine<ResourceEngine>()->GetResourceLoader<TextureResourceLoader>();

    for (auto animationJson : parsedJson)
    {
        AnimationDesc animationDesc;

        std::string name = animationJson["name"];
        animationDesc.name = name;

        auto spriteSheetJson = animationJson.find("spritesheet");
        if (spriteSheetJson == animationJson.end())
        {
            RED_LOG_WARNING("Path {} has no spritesheet attribute", p.string());
        }

        animationDesc.texture = textureResourceLoader->LoadResource(spriteSheetJson.value());

        animationDesc.loop = animationJson["loop"];

        auto framesJson = animationJson.find("frames");
        if (framesJson == animationJson.end())
        {
            RED_LOG_WARNING("Animation {} has no frame", name);
            continue;
        }

        for (auto& frameIt : framesJson.value())
        {
            auto rect = frameIt.find("rect").value();
            auto size = frameIt.find("size").value();
            auto duration = frameIt.find("duration").value();
            auto center = frameIt.find("center").value();

            AnimationFrameDesc frameDesc;
            frameDesc.rect = {rect["x"], rect["y"], rect["w"], rect["h"]};
            frameDesc.duration = duration;
            frameDesc.size = {size["w"], size["h"]};
            frameDesc.center = {center["x"], center["y"]};
            frameDesc.flipH = frameIt["flip_h"];
            frameDesc.flipV = frameIt["flip_v"];
            frameDesc.rotation = frameIt["rotation"];

            animationDesc.frames.push_back(frameDesc);
        }

        spriteResource->m_animations.push_back(animationDesc);
    }

    spriteResource->SetLoadState(LoadState::STATE_LOADED);

    return spriteResource;
}

}  // namespace red