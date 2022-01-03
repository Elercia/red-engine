#pragma once

#include "RedEngine/Resources/Resource.hpp"

namespace red
{
class ShaderProgram;

class Material : public IResource
{
public:
    RED_RESOURCE(ResourceType::MATERIAL);

    Material(const Path& resourceId);
    ~Material();

private:
    ShaderProgram* m_vertexShader;
};
}  // namespace red
