#include <RedEngine/Core/Components/Sprite.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>
#include <RedEngine/Rendering/RenderingEngine.hpp>
#include <RedEngine/Debug/Debug.hpp>
#include <RedEngine/Debug/Logger/Logger.hpp>
#include <RedEngine/Rendering/Texture.hpp>

namespace red
{
ResourceEngine::ResourceEngine() {}
ResourceEngine::~ResourceEngine()
{
    for (auto& resourceListPair : m_loadedResources)
    {
        for (auto& resourceItem : resourceListPair.second)
            delete resourceItem;
    }
}

Texture* ResourceEngine::LoadTexture(const std::string& path)
{
    return GetRedInstance().GetResourceEngine()->LoadTextureInternal(path);
}

Texture* ResourceEngine::LoadTextureInternal(const std::string& path)
{
    auto* texture = new Texture(Texture::GetNextResourceId());
    texture->m_loadState = LoadState::STATE_ERROR;  // At the end, the texture should either be
                                                    // loaded or not (if an error occurred)

    // Keep a reference to the created texture
    AddResourceToLoadedResources(ResourceType::TEXTURE, texture);

    SDL_Surface* tempSurface = SDL_LoadBMP(path.c_str());

    if (tempSurface == nullptr)
    {
        RED_LOG_WARNING("Error creating surface from texture path {} with error {}", path,
                        SDL_GetError());

        return texture;
    }

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

void ResourceEngine::ReleaseTexture(Texture* texture)
{
    SDL_DestroyTexture(texture->m_sdlTexture);
    texture->m_loadState = LoadState::STATE_NOT_LOADED;
}
void ResourceEngine::AddResourceToLoadedResources(ResourceType::Enum type, Resource* resource)
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