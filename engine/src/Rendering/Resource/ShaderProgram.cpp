#include "RedEngine/Rendering/Resource/ShaderProgram.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"
#include "GL/gl3w.h"

namespace red
{
ShaderProgram::ShaderProgram(const Path& resourceId)
    : IResource(resourceId, ResourceType::SHADER_PROGRAM), m_type(ShaderProgramType::Unknown), m_handle(0)
{
}

ShaderProgram::~ShaderProgram()
{
}

}  // namespace red
