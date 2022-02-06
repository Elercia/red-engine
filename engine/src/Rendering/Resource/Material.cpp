#include "RedEngine/Rendering/Resource/Material.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Rendering/Resource/ShaderProgram.hpp"
#include "RedEngine/Resources/Resource.hpp"

#include <GL/gl3w.h>

namespace red
{
Material::Material(const Path& resourceId) : IResource(resourceId, ResourceType::MATERIAL)
{
}

Material::~Material()
{
}

RenderEntityType Material::GetRenderType()
{
    return m_type;
}

std::shared_ptr<ShaderProgram> Material::GetShaderProgram()
{
	return m_shaderProgram;
}

int Material::GetInputLocation(const char* name)
{
	return glGetUniformLocation(m_shaderProgram->m_handle, name);
}

}  // namespace red