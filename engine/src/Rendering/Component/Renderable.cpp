#include "RedEngine/Rendering/Component/Renderable.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(Renderable)

Renderable::Renderable(Entity* owner) : Component(owner)
{
}

Renderable::~Renderable()
{
}

}  // namespace red
