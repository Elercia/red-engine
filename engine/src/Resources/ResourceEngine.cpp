#include <RedEngine/Core/Components/Sprite.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>
#include <RedEngine/Rendering/RenderingEngine.hpp>
#include <RedEngine/Core/Debug/Debug.hpp>
#include <RedEngine/Core/Debug/Logger/Logger.hpp>
#include <RedEngine/Core/Engine.hpp>
#include <RedEngine/Rendering/Texture2D.hpp>
#include <RedEngine/Utils/FileUtils.hpp>

#include <SDL2/SDL_image.h>
#include <nlohmann/json.hpp>

#include <filesystem>

namespace red
{
ResourceEngine::ResourceEngine() {}
ResourceEngine::~ResourceEngine()
{
    for (auto& resourceListPair : m_loadedResources)
    {
        for (auto& resourceItem : resourceListPair.second)
        {
            resourceItem->Release();
            resourceItem.reset();
        }

        resourceListPair.second.clear();
    }
}

std::shared_ptr<Texture2D> ResourceEngine::LoadTexture(const std::string& resourceId)
{
    // TODO path should be transformed into a specific resource identifier to allow data packaging
    return GetRedSubEngine<ResourceEngine>()->LoadTextureInternal(resourceId);
}

void ResourceEngine::LoadSprite(const std::string& resourceId, Sprite* sprite)
{
    GetRedSubEngine<ResourceEngine>()->LoadSpriteInternal(resourceId, sprite);
}

std::shared_ptr<Texture2D> ResourceEngine::LoadTextureInternal(const std::string& resourceId)
{
    // TODO if the texture exists, return it instead of making another
    namespace fs = std::filesystem;
    fs::path p = GetRedSubEngine<Configuration>()->GetResourceFolder() + "/" + resourceId;

    auto texture = std::make_shared<Texture2D>(Texture2D::GetNextResourceId());
    texture->m_loadState = LoadState::STATE_ERROR;  // At the end, the texture should either be
                                                    // loaded or not (if an error occurred)

    // Keep a reference to the created texture
    AddResourceToLoadedResources(ResourceType::TEXTURE2D, texture);

    SDL_Surface* tempSurface = IMG_Load(p.string().c_str());

    if (tempSurface == nullptr)
    {
        RED_LOG_WARNING("Error creating surface from texture path {} with error {}", p.string(),
                        SDL_GetError());

        return texture;
    }

    texture->m_sdlTexture = SDL_CreateTextureFromSurface(
        GetRedSubEngine<RenderingEngine>()->GetRenderer(), tempSurface);

    SDL_FreeSurface(tempSurface);

    if (texture->m_sdlTexture == nullptr)
    {
        RED_LOG_WARNING("Error creating texture for sprite path {} with error {}", p.string(),
                        SDL_GetError());

        return texture;
    }

    int h;
    int w;
    SDL_QueryTexture(texture->m_sdlTexture, nullptr, nullptr, &w, &h);

    texture->m_textureSize.h = h;
    texture->m_textureSize.w = w;

    texture->m_loadState = LoadState::STATE_LOADED;

    RED_LOG_INFO("Creating texture ID : {} from path {}", texture->GetResourceId(), p.string());

    return texture;
}

void ResourceEngine::ReleaseTexture(Texture2D* texture, bool erase)
{
    if (texture->GetLoadState() == LoadState::STATE_LOADED)
    {
        SDL_DestroyTexture(texture->m_sdlTexture);
    }

    texture->m_loadState = LoadState::STATE_NOT_LOADED;

    auto it = m_loadedResources.find(ResourceType::TEXTURE2D);
    auto& vect = it->second;

    auto foundIt = std::find_if(vect.begin(), vect.end(), [texture](const auto& value) {
        if (value == nullptr)
            return false;
        return texture->GetResourceId() == value->GetResourceId();
    });

    if (foundIt == vect.end())
    {
        RED_LOG_WARNING("Attempted to release a not found texture2D from resource (id:{})",
                        texture->m_resourceId);
        return;
    }

    auto& smartPtr = *foundIt;
    if (smartPtr.use_count() != 1)
    {
        RED_LOG_WARNING(
            "Attempted to release a texture2D resource that is used elsewhere (id:{}, use_count:)",
            texture->m_resourceId, smartPtr.use_count());

        return;
    }

    RED_LOG_INFO("Release texture ID : {}", texture->GetResourceId());

    if (erase)
        vect.erase(foundIt);
}
void ResourceEngine::AddResourceToLoadedResources(ResourceType::Enum type,
                                                  const std::shared_ptr<Texture2D>& resource)
{
    auto it = m_loadedResources.find(type);
    if (it != m_loadedResources.end())
    {
        it->second.push_back(resource);
    }
    else
    {
        m_loadedResources.insert({type, {resource}});
    }
}

void ResourceEngine::LoadLevel(const std::string& levelName) { RED_ABORT("Not implemented"); }

std::shared_ptr<Texture2D> ResourceEngine::CreateTextureFrom(SDL_Texture* sdlTexture)
{
    return GetRedSubEngine<ResourceEngine>()->CreateTextureFromInternal(sdlTexture);
}

std::shared_ptr<Texture2D> ResourceEngine::CreateTextureFromInternal(SDL_Texture* sdlTexture)
{
    auto texture = std::make_shared<Texture2D>(Texture2D::GetNextResourceId());
    texture->m_loadState = LoadState::STATE_LOADED;

    // Keep a reference to the created texture
    AddResourceToLoadedResources(ResourceType::TEXTURE2D, texture);

    texture->m_sdlTexture = sdlTexture;

    int h;
    int w;
    SDL_QueryTexture(texture->m_sdlTexture, nullptr, nullptr, &w, &h);

    texture->m_textureSize.h = h;
    texture->m_textureSize.w = w;

    return texture;
}

void ResourceEngine::LoadSpriteInternal(const std::string& resourceId, Sprite* sprite)
{
    namespace fs = std::filesystem;
    fs::path p = GetRedSubEngine<Configuration>()->GetResourceFolder() + "/" + resourceId + ".json";

    if (!fs::exists(p) || fs::is_directory(p))
    {
        RED_LOG_WARNING("Cannot load sprite for path {}", p.string());
        return;
    }

    using json = nlohmann::json;

    auto parsedJson = json::parse(ReadFile(p.string()), nullptr, false);

    if (parsedJson.is_discarded() || !parsedJson.is_array())
    {
        // TODO in case of an error, do something to handle this
        RED_LOG_WARNING("Path {} is not a valid JSON", p.string());
        return;
    }

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

        animationDesc.texture = LoadTextureInternal(spriteSheetJson.value());

        animationDesc.loop = animationJson["loop"];

        auto framesJson = animationJson.find("frames");
        if (framesJson == animationJson.end())
        {
            RED_LOG_WARNING("Animation {} has no frame", name);
            continue;
        }

        for (auto& it : framesJson.value())
        {
            auto rect = it.find("rect").value();
            auto size = it.find("size").value();
            auto duration = it.find("duration").value();
            auto center = it.find("center").value();

            AnimationFrameDesc frameDesc;
            frameDesc.rect = {rect["x"], rect["y"], rect["w"], rect["h"]};
            frameDesc.duration = duration;
            frameDesc.size = {size["w"], size["h"]};
            frameDesc.center = {center["x"], center["y"]};
            frameDesc.flipH = it["flip_h"];
            frameDesc.flipV = it["flip_v"];
            frameDesc.rotation = it["rotation"];

            animationDesc.frames.push_back(frameDesc);
        }

        sprite->m_animations.push_back(animationDesc);
    }
}

}  // namespace red