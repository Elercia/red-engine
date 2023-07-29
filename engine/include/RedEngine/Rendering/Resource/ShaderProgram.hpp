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
    friend class Material;

public:
    RED_RESOURCE(ResourceType::SHADER_PROGRAM, L"shader");

public:
    ShaderProgram(const Path& resourceId);
    ~ShaderProgram();

private:
    ShaderProgramType m_type;
    int m_handle;
};
}  // namespace red
