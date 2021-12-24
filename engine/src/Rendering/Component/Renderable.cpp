#include "RedEngine/Rendering/RenderingModule.hpp"
#include "RedEngine/Rendering/Component/Renderable.hpp"

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
