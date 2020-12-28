#include "RedEngine/Rendering/Resource/TextureResourceLoader.hpp"

#include "SDL2/SDL_image.h"
#include "nlohmann/json.hpp"

#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Resources/AnnimationDescriptor.hpp"
#include "RedEngine/Utils/FileUtils.hpp"

#include <filesystem>

namespace red
{
TextureResourceLoader::TextureResourceLoader() : ResourceLoader("Texture2D", ResourceType::TEXTURE2D) {}

TextureResourceLoader::~TextureResourceLoader() {}

std::shared_ptr<Texture2D> TextureResourceLoader::LoadResource(const std::string& name)
{
    namespace fs = std::filesystem;

    auto resourcePtr = GetOrCreateFromCache(name);

    if (resourcePtr != nullptr)
    {
        return resourcePtr;
    }

    fs::path p = GetSubEngine<Configuration>()->GetResourceFolder() + "/" + name;

    auto texture = std::make_shared<Texture2D>(name);

    texture->SetLoadState(LoadState::STATE_ERROR);  // At the end, the texture should either be
                                                    // loaded or not (if an error occurred)

    SDL_Surface* tempSurface = IMG_Load(p.string().c_str());

    if (tempSurface == nullptr)
    {
        RED_LOG_WARNING("Error creating surface from texture path {} with error {}", p.string(), SDL_GetError());

        return texture;
    }

    texture->m_sdlTexture = SDL_CreateTextureFromSurface(GetSubEngine<RenderingEngine>()->GetRenderer(), tempSurface);

    SDL_FreeSurface(tempSurface);

    if (texture->m_sdlTexture == nullptr)
    {
        RED_LOG_WARNING("Error creating texture for sprite path {} with error {}", p.string(), SDL_GetError());

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

}  // namespace red