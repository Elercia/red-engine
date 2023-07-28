#include "RedEngine/Rendering/Resource/ShaderProgramResourceLoader.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

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


bool ShaderProgramResourceLoader::InitResource(std::shared_ptr<ShaderProgram>& resource, const Path& path, Json jsonContent)
{
    if (jsonContent[SHADER_TYPE] == "vertex_pixel")
        resource->m_type = ShaderProgramType::Vertex_Pixel;
    else if (jsonContent[SHADER_TYPE] == "compute")
        resource->m_type = ShaderProgramType::Compute;
    else
    {
        RED_LOG_WARNING("Cannot load shader for path {} because shader type is not recognized", path.GetAscciiPath());
        return false;
    }

    if (resource->m_type == ShaderProgramType::Vertex_Pixel)
    {
        int vertexHandle =
            CompileShader(ShaderType::Vertex, Path::Resource(String(jsonContent[VERTEX_SHADER_PATH])));
        int pixelHandle = CompileShader(ShaderType::Pixel, Path::Resource(String(jsonContent[PIXEL_SHADER_PATH])));

        if (vertexHandle == -1 || pixelHandle == -1)
        {
            RED_LOG_ERROR("Failed to load shader program because one of the shader couldn't compile");
            return false;
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
                Array<GLchar> infoLog;
                infoLog.resize(maxLength);
                glGetProgramInfoLog(programHandle, maxLength, &maxLength, &infoLog[0]);

                RED_LOG_WARNING("Cannot link shader program for path {} because of the following error : {}",
                                path.GetAscciiPath(), infoLog.data());
            }
        }

        glDetachShader(programHandle, vertexHandle);
        glDetachShader(programHandle, pixelHandle);

        glDeleteShader(vertexHandle);
        glDeleteShader(pixelHandle);

        resource->m_handle = programHandle;
        if (!bOk)
        {
            resource->m_handle = -1;
            glDeleteProgram(programHandle);
            return false;
        }
    }
    else
    {
        RED_LOG_ERROR("Not implemented");
        return false;
    }

    return true;
}

void ShaderProgramResourceLoader::FinalizeResource(std::shared_ptr<ShaderProgram> resource)
{
    resource->SetLoadState(LoadState::STATE_RELEASED);
}

int ShaderProgramResourceLoader::CompileShader(ShaderType type, const Path& path)
{
    const String shaderCode = ReadFile(path);

    static const GLuint openglTypes[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_COMPUTE_SHADER};

    GLuint GLShaderType = openglTypes[(int) type];
    GLuint handle = glCreateShader(GLShaderType);

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
