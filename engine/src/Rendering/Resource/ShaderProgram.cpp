#include "RedEngine/Rendering/Resource/ShaderProgram.hpp"

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
