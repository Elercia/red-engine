#pragma once

#include "RedEngine/Core/Container/Map.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"
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

enum class ValueType
{
    TEXTURE, 
    VECTOR4
};

struct ParameterValue
{
    ValueType type;

    std::shared_ptr<Texture2D> texture;
    Vector4 vector;
};

// Struct that contains resource that are bound to the current material
struct MaterialParameter
{
    Map<std::string, ParameterValue> parameters; // TODO simple c-array with direct input location as index
};

class Material;

struct MaterialInstance
{
    std::shared_ptr<Material> material;
    MaterialParameter parameters;
};

class Material : public IResource
{
    friend class MaterialResourceLoader;
    friend class Renderer;

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
    MaterialParameter m_defaultMaterialData;
};
}  // namespace red
