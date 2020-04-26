#include <RedEngine/Core/Components/Sprite.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>
#include <RedEngine/Rendering/RenderingEngine.hpp>
#include <RedEngine/Debug/Debug.hpp>
#include <RedEngine/Debug/Logger/Logger.hpp>
#include <RedEngine/Core/Engine.hpp>
#include <RedEngine/Rendering/Texture2D.hpp>

namespace red
{
ResourceEngine::ResourceEngine() {}
ResourceEngine::~ResourceEngine()
{
    for (auto& resourceListPair : m_loadedResources)
    {
        for (auto& resourceItem : resourceListPair.second)
            resourceItem.reset();
    }
}

std::shared_ptr<Texture2D> ResourceEngine::LoadTexture(const std::string& path)
{
    return GetRedInstance().GetResourceEngine()->LoadTextureInternal(path);
}

std::shared_ptr<Texture2D> ResourceEngine::LoadTextureInternal(const std::string& path)
{
    auto texture = std::make_shared<Texture2D>(Texture2D::GetNextResourceId());
    texture->m_loadState = LoadState::STATE_ERROR;  // At the end, the texture should either be
                                                    // loaded or not (if an error occurred)

    // Keep a reference to the created texture
    AddResourceToLoadedResources(ResourceType::TEXTURE2D, texture);

    SDL_Surface* tempSurface = SDL_LoadBMP(path.c_str());

    if (tempSurface == nullptr)
    {
        RED_LOG_WARNING("Error creating surface from texture path {} with error {}", path,
                        SDL_GetError());

        return texture;
    }

    sprite->m_texture = SDL_CreateTextureFromSurface(
        GetRedSubEngine<RenderingEngine>()->GetRenderer(), tempSurface);
    texture->m_sdlTexture = SDL_CreateTextureFromSurface(
        GetRedInstance().GetRenderingEngine()->GetRenderer(), tempSurface);

    SDL_FreeSurface(tempSurface);

    if (texture->m_sdlTexture == nullptr)
    {
        RED_LOG_WARNING("Error creating texture for sprite path {} with error {}", path,
                        SDL_GetError());

        return texture;
    }

    int h;
    int w;
    SDL_QueryTexture(texture->m_sdlTexture, nullptr, nullptr, &w, &h);

    texture->m_textureSize.h = h;
    texture->m_textureSize.w = w;

    texture->m_loadState = LoadState::STATE_LOADED;

    return texture;
}

void ResourceEngine::ReleaseTexture(Texture2D* texture, bool force)
{
    SDL_DestroyTexture(texture->m_sdlTexture);
    texture->m_loadState = LoadState::STATE_NOT_LOADED;

    auto it = m_loadedResources.find(ResourceType::TEXTURE2D);
    auto& vect = it->second;

    auto foundIt = std::find_if(vect.begin(), vect.end(), [texture](const auto& value) {
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

        if (!force)
            return;
    }

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
}  // namespace red