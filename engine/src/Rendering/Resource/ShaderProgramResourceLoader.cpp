#include "RedEngine/Rendering/RenderingModule.hpp"
#include "RedEngine/Rendering/Resource/ShaderProgramResourceLoader.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Utils/FileUtils.hpp"
#include "RedEngine/Utils/StringUtils.hpp"

#include <GL/gl3w.h>
#include <filesystem>
#include <nlohmann/json.hpp>

constexpr const char* SHADER_TYPE = "type";
constexpr const char* VERTEX_SHADER_PATH = "vertex_path";
constexpr const char* PIXEL_SHADER_PATH = "pixel_path";
constexpr const char* COMPUTE_SHADER_PATH = "compute_path";

namespace red
{
ShaderProgramResourceLoader::ShaderProgramResourceLoader(World* world) : ResourceLoader(ResourceType::SPRITE, world)
{
}

ShaderProgramResourceLoader::~ShaderProgramResourceLoader()
{
}

std::shared_ptr<ShaderProgram> ShaderProgramResourceLoader::LoadResource(const Path& path)
{
    using json = nlohmann::json;

    Path activePath = path;
    activePath.Append(L".json");

    auto shaderResource = GetOrCreateFromCache(activePath);

    if (shaderResource->GetLoadState() == LoadState::STATE_LOADED)
        return shaderResource;

    shaderResource->SetLoadState(LoadState::STATE_ERROR);

    if (!activePath.Exist() || activePath.IsDirectory())
    {
        RED_LOG_WARNING("Cannot load shader for path {}", activePath.GetAscciiPath());
        return nullptr;
    }

    auto shaderStr = ReadFile(activePath);

    if (shaderStr.empty())
    {
        RED_LOG_WARNING("Cannot load shader for path {}", path.GetAscciiPath());
        return shaderResource;
    }

    auto shaderJson = json::parse(shaderStr);
    if (shaderJson.empty())
    {
        RED_LOG_WARNING("Cannot load shader for path {}", path.GetAscciiPath());
        return shaderResource;
    }

    if (shaderJson[SHADER_TYPE] == "vertex_pixel")
        shaderResource->m_type = ShaderProgramType::Vertex_Pixel;
    else if (shaderJson[SHADER_TYPE] == "compute")
        shaderResource->m_type = ShaderProgramType::Compute;
    else
    {
        RED_LOG_WARNING("Cannot load shader for path {}", path.GetAscciiPath());
        return shaderResource;
    }

    if (shaderResource->m_type == ShaderProgramType::Vertex_Pixel)
    {
        int vertexHandle =
            CompileShader(ShaderType::Vertex, Path::Resource(std::string(shaderJson[VERTEX_SHADER_PATH])));
        int pixelHandle = CompileShader(ShaderType::Pixel, Path::Resource(std::string(shaderJson[PIXEL_SHADER_PATH])));

        if (vertexHandle == -1 || pixelHandle == -1)
        {
            RED_LOG_ERROR("Failed to load shader program because one of the shader couldn't compile");
            return shaderResource;
        }

        int programHandle = glCreateProgram();
        glAttachShader(programHandle, vertexHandle);
        glAttachShader(programHandle, pixelHandle);

        glLinkProgram(programHandle);

        bool bOk = true;
        {
            GLint isLinked = 0;
            glGetProgramiv(programHandle, GL_LINK_STATUS, (int*) &isLinked);
            if (isLinked == GL_FALSE)
            {
                bOk = false;
                GLint maxLength = 0;
                glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetProgramInfoLog(programHandle, maxLength, &maxLength, &infoLog[0]);

                RED_LOG_WARNING("Cannot compile shader for path {} because of the following error : {}",
                                path.GetAscciiPath(), infoLog.data());
            }
        }

        glDetachShader(programHandle, vertexHandle);
        glDetachShader(programHandle, pixelHandle);

        glDeleteShader(vertexHandle);
        glDeleteShader(pixelHandle);

        shaderResource->m_handle = programHandle;
        if (!bOk)
        {
            shaderResource->m_handle = -1;
            glDeleteProgram(programHandle);
            return shaderResource;
        }
    }
    else
    {
        RED_LOG_ERROR("Not implemented");
        return shaderResource;
    }

    shaderResource->SetLoadState(LoadState::STATE_LOADED);

    return shaderResource;
}

void ShaderProgramResourceLoader::FreeResource(std::shared_ptr<ShaderProgram> resource)
{
    resource->SetLoadState(LoadState::STATE_RELEASED);
}

int ShaderProgramResourceLoader::CompileShader(ShaderType type, const Path& path)
{
    const std::string shaderCode = ReadFile(path);

    const GLuint openglTypes[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_COMPUTE_SHADER};

    GLuint ShaderTypeGL = openglTypes[(int) type];
    GLuint handle = glCreateShader(ShaderTypeGL);

    {
        const char* shaderData = shaderCode.data();
        glShaderSource(handle, 1, &shaderData, nullptr);
        glCompileShader(handle);

        {
            int status;
            glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
            if (status == GL_FALSE)
            {
                int logLength = 0;
                glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLength);
                if (logLength > 1)
                {
                    char* logData = new char[logLength];
                    glGetShaderInfoLog(handle, logLength, &logLength, logData);

                    RED_LOG_WARNING("Cannot compile shader for path {} because of the following error : {}",
                                    path.GetAscciiPath(), logData);

                    delete[] logData;
                }
                else
                {
                    RED_LOG_WARNING("Cannot compile shader for path {} but couldn't recover error",
                                    path.GetAscciiPath());
                }

                glDeleteShader(handle);

                return -1;
            }
        }
    }

    return handle;
}

}  // namespace red
