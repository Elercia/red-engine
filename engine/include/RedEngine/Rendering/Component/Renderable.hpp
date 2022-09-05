#pragma once

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Rendering/Resource/Geometry.hpp"
#include "RedEngine/Rendering/Resource/Material.hpp"
#include "RedEngine/Math/AABB.hpp"

namespace red
{
class Renderable;

RED_COMPONENT_BASIC_FUNCTIONS_DECLARATION(Renderable)

using RenderLayerIndex = uint32;

class Renderable : public Component
{
    friend class Renderer;

public:
    RED_START_COMPONENT_REGISTER_INHERITHED(Renderable, Component)
    //TODO add geom & material
    RED_END_COMPONENT_REGISTER()

public:
    Renderable(Entity* owner);
    Renderable(Entity* owner, RenderLayerIndex layerIndex);
    ~Renderable();

    MaterialInstance GetMaterial();
    std::shared_ptr<GeometryResourceWrapper> GetGeometry();

    void SetRenderLayerIndex(RenderLayerIndex layerIndex);
    RenderLayerIndex GetRenderLayerIndex() const;

protected:
    RenderLayerIndex m_layerIndex;
    Vector2 m_size;
    AABB m_aabb;
    std::shared_ptr<GeometryResourceWrapper> m_geometry;
    MaterialInstance m_material;
};
}  // namespace red
