#include "RedEngine/Rendering/Component/Renderable.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"
#include "RedEngine/Rendering/Resource/Material.hpp"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(Renderable)

Renderable::Renderable(Entity* owner) : Component(owner)
{
}

Renderable::~Renderable()
{
}

MaterialInstance Renderable::GetMaterial()
{
    return m_material;
}

std::shared_ptr<GeometryResourceWrapper> Renderable::GetGeometry()
{
    return m_geometry;
}

}  // namespace red
