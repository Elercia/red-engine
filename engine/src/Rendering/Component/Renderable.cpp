#include "RedEngine/Rendering/Component/Renderable.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Rendering/Resource/Material.hpp"

namespace red
{
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

void Renderable::SetMaterialInstance(const MaterialInstance& instance)
{
    m_material = instance;
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

bool Renderable::IsValid() const
{
    return m_size.x != 0 && m_size.y != 0 && m_geometry != nullptr && m_material.material != nullptr;
}

void Renderable::SetGeometry(std::shared_ptr<GeometryResourceWrapper> geom)
{
    m_geometry = geom;
}

AABB& Renderable::GetAABB()
{
    return m_aabb;
}

void Renderable::SetAABB(const AABB& aabb)
{
    m_aabb = aabb;
}

Vector2& Renderable::GetSize()
{
    return m_size;
}

void Renderable::SetSize(const Vector2& size)
{
    m_size = size;
}

}  // namespace red
