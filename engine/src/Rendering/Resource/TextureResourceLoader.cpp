#include "RedEngine/Rendering/Resource/TextureResourceLoader.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

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

bool TextureResourceLoader::InitResource(std::shared_ptr<Texture2D>& resource, const Path& path,
                                         nlohmann::json jsonContent)
{
    std::string asciiPath = jsonContent["file"];

    Path resourcePath = Path::Resource(asciiPath);

    int nrChannels;
    unsigned char* data =
        stbi_load(resourcePath.GetAscciiPath().c_str(), &resource->m_size.width, &resource->m_size.height, &nrChannels, 0);

    if (data == nullptr)
    {
        RED_LOG_WARNING("Error creating surface from texture path {} with error {}", path.GetAscciiPath(),
                        stbi_failure_reason());

        return false;
    }

    glGenTextures(1, &resource->m_textureHandle);
    glBindTexture(GL_TEXTURE_2D, resource->m_textureHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resource->m_size.width, resource->m_size.height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 data);  // TODO change format of the texture from the read channel data or user defined format
    glGenerateMipmap(GL_TEXTURE_2D);  // TODO make a macro to check opengl errors like described
                                      // https://www.khronos.org/opengl/wiki/OpenGL_Error

    stbi_image_free(data);

    return true;
}

void TextureResourceLoader::FinalizeResource(std::shared_ptr<Texture2D> resource)
{
    glDeleteTextures(1, &resource->m_textureHandle);

    resource->SetLoadState(LoadState::STATE_RELEASED);
}

}  // namespace red