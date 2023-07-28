#include "RedEngine/Rendering/Resource/SpriteResourceLoader.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

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

bool SpriteResourceLoader::InitResource(std::shared_ptr<SpriteResource>& resource, const Path& path,
                                        Json jsonContent)
{
    auto* textureResourceLoader =
        m_world->GetWorldComponent<ResourceHolderComponent>()->GetResourceLoader<TextureResourceLoader>();

    auto* materialLoader =
        m_world->GetWorldComponent<ResourceHolderComponent>()->GetResourceLoader<MaterialResourceLoader>();

    for (auto animationJson : jsonContent)
    {
        AnimationDesc animationDesc;

        String animationName = animationJson["name"];
        animationDesc.name = animationName;

        auto spriteSheetJson = animationJson.find("spritesheet");
        if (spriteSheetJson == animationJson.end())
        {
            RED_LOG_WARNING("Path {} has no spritesheet attribute", path.GetAscciiPath());
        }

        String spriteSheetPathStr = spriteSheetJson.value();
        animationDesc.texture =
            textureResourceLoader->LoadResource(Path::Resource(utils::ToUnicodeString(spriteSheetPathStr)));

        String materialName = animationJson["material"];
        animationDesc.material = materialLoader->LoadResource(Path::Resource(utils::ToUnicodeString(materialName)));

        auto framesJson = animationJson.find("frames");
        if (framesJson == animationJson.end())
        {
            RED_LOG_WARNING("Animation {} has no frame", animationName);
            continue;
        }

        animationDesc.loop = animationJson["loop"];

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

        resource->m_animations.push_back(animationDesc);
    }

    return true;
}

void SpriteResourceLoader::FinalizeResource(std::shared_ptr<SpriteResource> resource)
{
    resource->SetLoadState(LoadState::STATE_RELEASED);
}

}  // namespace red
