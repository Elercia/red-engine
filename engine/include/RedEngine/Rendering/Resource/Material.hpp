#pragma once

#include "RedEngine/Resources/Resource.hpp"

#include <memory>
#include <string_view>

namespace red
{
class ShaderProgram;

enum RenderEntityType
{
    Opaque,
    Transparency,
    Count,
};

class Material : public IResource
{
    friend class MaterialResourceLoader;

public:
    RED_RESOURCE(ResourceType::MATERIAL);

    Material(const Path& resourceId);
    ~Material();

    int GetInputLocation(const char* name);

    std::shared_ptr<ShaderProgram> GetShaderProgram();
    RenderEntityType GetRenderType();

private:
    std::shared_ptr<ShaderProgram> m_shaderProgram{nullptr};
    RenderEntityType m_type{RenderEntityType::Opaque};
};
}  // namespace red
