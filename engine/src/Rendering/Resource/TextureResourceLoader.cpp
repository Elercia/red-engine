#include "RedEngine/Rendering/Resource/TextureResourceLoader.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Resources/AnnimationDescriptor.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"
#include "RedEngine/Utils/FileUtils.hpp"

#include <SDL2/SDL_image.h>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace red
{
TextureResourceLoader::TextureResourceLoader(World* world) : ResourceLoader(ResourceType::TEXTURE2D, world)
{
}

TextureResourceLoader::~TextureResourceLoader()
{
}

std::shared_ptr<Texture2D> TextureResourceLoader::LoadResource(const Path& path)
{
    namespace fs = std::filesystem;

    auto resourcePtr = GetOrCreateFromCache(path);

    if (resourcePtr != nullptr && resourcePtr->GetLoadState() == LoadState::STATE_LOADED)
    {
        return resourcePtr;
    }

    auto texture = std::make_shared<Texture2D>(path);

    texture->SetLoadState(LoadState::STATE_ERROR);  // At the end, the texture should either be
                                                    // loaded or not (if an error occurred)

    std::string asciiPath = path.GetAscciiPath();
    SDL_Surface* tempSurface = IMG_Load(asciiPath.data());

    if (tempSurface == nullptr)
    {
        RED_LOG_WARNING("Error creating surface from texture path {} with error {}", asciiPath, SDL_GetError());

        return texture;
    }

    texture->m_sdlTexture = nullptr;

    auto* renderingSystem = m_world->GetSystem<RenderingSystem>();
    if (renderingSystem != nullptr && renderingSystem->GetRenderer() != nullptr)
        texture->m_sdlTexture =
            SDL_CreateTextureFromSurface(renderingSystem->GetRenderer()->GetSDLRenderer(), tempSurface);

    SDL_FreeSurface(tempSurface);

    if (texture->m_sdlTexture == nullptr)
    {
        RED_LOG_WARNING("Error creating texture for sprite path {} with error {}", asciiPath, SDL_GetError());

        return texture;
    }

    int h;
    int w;
    SDL_QueryTexture(texture->m_sdlTexture, nullptr, nullptr, &w, &h);

    texture->m_textureSize.h = h;
    texture->m_textureSize.w = w;

    texture->m_loadState = LoadState::STATE_LOADED;

    RED_LOG_INFO("Creating texture from path {}", asciiPath);

    return texture;
}

void TextureResourceLoader::FreeResource(std::shared_ptr<Texture2D> resource)
{
    SDL_DestroyTexture(resource->m_sdlTexture);

    resource->SetLoadState(LoadState::STATE_RELEASED);
}

}  // namespace red