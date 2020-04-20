#include <RedEngine/Rendering/Components/Sprite.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>
#include <RedEngine/Rendering/RenderingEngine.hpp>
#include <RedEngine/Debug/Debug.hpp>
#include <RedEngine/Debug/Logger/Logger.hpp>

namespace red
{
ResourceEngine::ResourceEngine() {}
ResourceEngine::~ResourceEngine() {}

bool ResourceEngine::ImportSprite(Sprite* sprite)
{
    SDL_Surface* tempSurface = SDL_LoadBMP(sprite->m_path.c_str());

    if (tempSurface == nullptr)
    {
        RED_LOG_WARNING("Error creating surface from sprite path {} with error {}", sprite->m_path,
                        SDL_GetError());
        sprite->m_isLoaded = LoadState::STATE_ERROR;
        return false;
    }

    sprite->m_texture = SDL_CreateTextureFromSurface(
        GetRedInstance().GetRenderingEngine()->GetRenderer(), tempSurface);

    SDL_FreeSurface(tempSurface);

    if (sprite->m_texture == nullptr)
    {
        RED_LOG_WARNING("Error creating texture for sprite path {} with error {}", sprite->m_path,
                        SDL_GetError());
        sprite->m_isLoaded = LoadState::STATE_ERROR;
        return false;
    }

    int h;
    int w;
    SDL_QueryTexture(sprite->m_texture, nullptr, nullptr, &w, &h);

    sprite->m_sdlSize.h = h;
    sprite->m_sdlSize.w = w;

    sprite->m_sdlPos.h = h;
    sprite->m_sdlPos.w = w;

    sprite->m_isLoaded = LoadState::STATE_LOADED;

    return true;
}
void ResourceEngine::FreeSprite(Sprite* mesh)
{
    SDL_DestroyTexture(mesh->m_texture);
    mesh->m_texture = nullptr;
    mesh->m_isLoaded = LoadState::STATE_NOT_LOADED;
}
}  // namespace red