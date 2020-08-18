#include <RedEngine/Physics/System/PhysicsSystem.hpp>

namespace red
{
PhysicSystem::PhysicSystem(World* world) : System(world) {}

PhysicSystem::~PhysicSystem() {}

void PhysicSystem::FixedUpdate()
{
    b2World* physicsWorld = m_world->GetPhysicsWorld();
    physicsWorld->Step(timeStep, velocityIterations, positionIterations);

    physicsWorld->ClearForces();
}

}  // namespace red