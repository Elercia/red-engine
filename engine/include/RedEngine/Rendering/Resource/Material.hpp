#pragma once

#include "RedEngine/Core/Container/Map.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"
#include "RedEngine/Resources/Resource.hpp"

#include <memory>
#include <string_view>

namespace red
{
class ShaderProgram;

enum class RenderEntityType : uint8
{
    Opaque,
    Transparency,
    Count,
};

enum class BindingType
{
    Undefined,
    Texture,
    Vector4
};

struct BindingIndex
{
    enum
    {
        Diffuse = 0,
        Color = 1,
        Max = 16,
    };
};

struct BindingValue
{
    BindingType type = BindingType::Undefined;

    union
    {
        Texture2D* texture;
        float floats[4];
    };
};

// Struct that contains resource that are bound to the current material
struct MaterialBindings
{
    BindingValue bindings[BindingIndex::Max];
};

class Material;

struct MaterialInstance
{
    std::shared_ptr<Material> material;
    MaterialBindings overriddenBindings;
};

class Material : public IResource
{
    friend class MaterialResourceLoader;
    friend class Renderer;

public:
    RED_RESOURCE(ResourceType::MATERIAL, L"material");

    Material(const Path& resourceId);
    ~Material();

    int GetInputLocation(const char* name);

    std::shared_ptr<ShaderProgram> GetShaderProgram();
    RenderEntityType GetRenderType();

private:
    std::shared_ptr<ShaderProgram> m_shaderProgram{nullptr};
    RenderEntityType m_type{RenderEntityType::Opaque};
    MaterialBindings m_defaultBindings;
};
}  // namespace red
