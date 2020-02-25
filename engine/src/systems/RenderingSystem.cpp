#include <RedEngine/components/Mesh.hpp>
#include <RedEngine/ecs/World.hpp>
#include <RedEngine/systems/RenderingSystem.hpp>

namespace red
{
RenderingSystem::RenderingSystem(World* world) : System(world) {}

void RenderingSystem::Update(float deltaTime)
{
    for(auto& entity : GetComponents<Mesh>())
    {

    }
}
} // namespace red
