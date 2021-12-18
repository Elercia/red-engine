#include "RedEngine/Rendering/Resource/TextureResourceLoader.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Resources/ResourceLoader.hpp"

#include <GL/gl3w.h>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <stbi/stb_image.h>

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

    resourcePtr->SetLoadState(LoadState::STATE_ERROR);  // At the end, the texture should either be
                                                        // loaded or not (if an error occurred)

    std::string asciiPath = path.GetAscciiPath();

    int nrChannels;
    unsigned char* data =
        stbi_load(asciiPath.c_str(), &resourcePtr->m_size.width, &resourcePtr->m_size.height, &nrChannels, 0);

    if (data == nullptr)
    {
        RED_LOG_WARNING("Error creating surface from texture path {} with error {}", asciiPath, stbi_failure_reason());

        return resourcePtr;
    }

    glGenTextures(1, &resourcePtr->m_textureHandle);
    glBindTexture(GL_TEXTURE_2D, resourcePtr->m_textureHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resourcePtr->m_size.width, resourcePtr->m_size.height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE,
                 data);  // TODO change format of the texture from the read channel data or user defined format
    glGenerateMipmap(GL_TEXTURE_2D);  // TODO make a macro to check opengl errors like described
                                      // https://www.khronos.org/opengl/wiki/OpenGL_Error

    stbi_image_free(data);

    resourcePtr->m_loadState = LoadState::STATE_LOADED;

    RED_LOG_INFO("Creating texture from path {}", asciiPath);

    return resourcePtr;
}

void TextureResourceLoader::FreeResource(std::shared_ptr<Texture2D> resource)
{
    glDeleteTextures(1, &resource->m_textureHandle);

    resource->SetLoadState(LoadState::STATE_RELEASED);
}

}  // namespace red