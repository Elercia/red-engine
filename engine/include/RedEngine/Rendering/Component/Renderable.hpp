#pragma once

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Rendering/Resource/Geometry.hpp"
#include "RedEngine/Rendering/Resource/Material.hpp"

namespace red
{
class Renderable;

RED_COMPONENT_BASIC_FUNCTIONS_DECLARATION(Renderable)

class Renderable : public Component
{
public:
    RED_START_COMPONENT_REGISTER_INHERITHED(Renderable, Component)
    RED_END_COMPONENT_REGISTER()

public:
    Renderable(Entity* owner);
    ~Renderable();

private:
    std::shared_ptr<Geometry> m_geometry;
    std::shared_ptr<Material> m_material;
};
}  // namespace red
