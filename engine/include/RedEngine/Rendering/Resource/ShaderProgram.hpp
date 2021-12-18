#pragma once

#include "RedEngine/Resources/Resource.hpp"

#include <string>

namespace red
{
enum class ShaderProgramType
{
    Vertex_Pixel,
    Compute,
    Unknown
};

class ShaderProgram : public IResource
{
    friend class ShaderProgramResourceLoader;
    friend class Renderer;

public:
    RED_RESOURCE(ResourceType::SHADER_PROGRAM);

public:
    ShaderProgram(const Path& resourceId);
    ~ShaderProgram();

private:
    ShaderProgramType m_type;
    int m_handle;
};
}
