#include "RedEngine/Rendering/Resource/SpriteResourceLoader.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Rendering/Resource/TextureResourceLoader.hpp"
#include "RedEngine/Resources/AnnimationDescriptor.hpp"
#include "RedEngine/Resources/ResourceHolderComponent.hpp"
#include "RedEngine/Utils/FileUtils.hpp"
#include "RedEngine/Utils/StringUtils.hpp"

#include <filesystem>
#include <nlohmann/json.hpp>

namespace red
{
SpriteResourceLoader::SpriteResourceLoader(World* world) : ResourceLoader(ResourceType::SPRITE, world)
{
}

SpriteResourceLoader::~SpriteResourceLoader()
{
}

std::shared_ptr<red::SpriteResource> SpriteResourceLoader::LoadResource(const Path& path)
{
    namespace fs = std::filesystem;
    using json = nlohmann::json;

    Path activePath = path;
    activePath.Append(L".json");

    auto spriteResource = GetOrCreateFromCache(activePath);

    if (spriteResource->GetLoadState() == LoadState::STATE_LOADED)
        return spriteResource;

    if (!activePath.Exist() || activePath.IsDirectory())
    {
        RED_LOG_WARNING("Cannot load sprite for path {}", activePath.GetAscciiPath());
        return nullptr;
    }

    auto parsedJson = json::parse(ReadFile(activePath), nullptr, false);

    if (parsedJson.is_discarded() || !parsedJson.is_array())
    {
        RED_LOG_WARNING("Path {} is not a valid JSON", activePath.GetAscciiPath());
        return nullptr;
    }

    auto* textureResourceLoader =
        m_world->GetSingletonComponent<ResourceHolderComponent>()->GetResourceLoader<TextureResourceLoader>();

    for (auto animationJson : parsedJson)
    {
        AnimationDesc animationDesc;

        std::string animationName = animationJson["name"];
        animationDesc.name = animationName;

        auto spriteSheetJson = animationJson.find("spritesheet");
        if (spriteSheetJson == animationJson.end())
        {
            RED_LOG_WARNING("Path {} has no spritesheet attribute", activePath.GetAscciiPath());
        }
        
        std::string spriteSheetPathStr = spriteSheetJson.value();

        animationDesc.texture =
            textureResourceLoader->LoadResource(Path::Resource(utils::ToUnicodeString(spriteSheetPathStr)));

        animationDesc.loop = animationJson["loop"];

        auto framesJson = animationJson.find("frames");
        if (framesJson == animationJson.end())
        {
            RED_LOG_WARNING("Animation {} has no frame", animationName);
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

void SpriteResourceLoader::FreeResource(std::shared_ptr<red::SpriteResource> resource)
{
    resource->SetLoadState(LoadState::STATE_RELEASED);
}

}  // namespace red
