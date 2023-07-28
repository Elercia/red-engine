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
                                         Json jsonContent)
{
    String asciiPath = jsonContent["file"];

    Path resourcePath = Path::Resource(asciiPath);

    int nbChannels;
    unsigned char* data = stbi_load(resourcePath.GetAscciiPath().c_str(), &resource->m_size.width,
                                    &resource->m_size.height, &nbChannels, 0);

    if (data == nullptr)
    {
        RED_LOG_WARNING("Error creating surface from texture path {} with error {}", path.GetAscciiPath(),
                        stbi_failure_reason());

        return false;
    }

    GLenum pixelFormatSized = nbChannels == 4 ? GL_RGBA8 : GL_RGB8;
    GLenum pixelFormat = nbChannels == 4 ? GL_RGBA : GL_RGB;

    RED_LOG_INFO("Creating texture {} ({}:{}) with {} channels", path.GetAscciiPath(), resource->m_size.width, resource->m_size.height, nbChannels);

    // TODO make a macro to check opengl errors like described
    // https://www.khronos.org/opengl/wiki/OpenGL_Error

    glCreateTextures(GL_TEXTURE_2D, 1, &resource->m_textureHandle);
    glTextureStorage2D(resource->m_textureHandle, 1, pixelFormatSized, resource->m_size.width, resource->m_size.height);
    glTextureSubImage2D(resource->m_textureHandle, 0, 0, 0, resource->m_size.width, resource->m_size.height, pixelFormat, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    return true;
}

void TextureResourceLoader::FinalizeResource(std::shared_ptr<Texture2D> resource)
{
    glDeleteTextures(1, &resource->m_textureHandle);

    resource->SetLoadState(LoadState::STATE_RELEASED);
}

}  // namespace red