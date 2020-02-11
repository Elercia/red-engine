#include <RedEngine/ecs/ComponentManager.hpp>
#include <RedEngine/systems/RenderingSystem.hpp>

namespace red
{
RenderingSystem::RenderingSystem(ComponentManager* componentManager) : System(componentManager) {}

void RenderingSystem::Update(float deltaTime) {}
} // namespace red
