#include "RedEngine/Rendering/Component/Renderable.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Rendering/Resource/Material.hpp"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(Renderable)

Renderable::Renderable(Entity* owner) : Component(owner), m_layerIndex(0)
{
}

Renderable::Renderable(Entity* owner, RenderLayerIndex layerIndex) : Component(owner), m_layerIndex(layerIndex)
{
}

Renderable::~Renderable()
{
}

MaterialInstance& Renderable::GetMaterial()
{
    return m_material;
}

const MaterialInstance& Renderable::GetMaterial() const
{
    return m_material;
}

std::shared_ptr<GeometryResourceWrapper> Renderable::GetGeometry()
{
    return m_geometry;
}

void Renderable::SetRenderLayerIndex(RenderLayerIndex layerIndex)
{
    m_layerIndex = layerIndex;
}

RenderLayerIndex Renderable::GetRenderLayerIndex() const
{
    return m_layerIndex;
}

}  // namespace red
