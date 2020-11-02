#pragma once

#include <RedEngine/Core/Entity/System.hpp>

class b2Contact;

namespace red
{
class PhysicsWorld;
class PhysicBody;
struct Collider;

class PhysicSystem : public System
{
public:
    PhysicSystem(World* world);
    ~PhysicSystem();

    void Init() override;
    void Finalise() override;

    void Update() override;

private:
    void ManageEntities();
    void ManageContacts();
    void ManageCollisionContact(PhysicBody* physicBody1, PhysicBody* physicBody2,
                                Collider* collider1, Collider* collider2, const b2Contact* contact);
    void ManageTriggerContact(PhysicBody* physicBody1, PhysicBody* physicBody2, Collider* collider1,
                              Collider* collider2, const b2Contact* contact);

private:
    PhysicsWorld* m_physicsWorld;
    float timeStep = 1.0f / 60.f;
    int32 velocityIterations = 10;
    int32 positionIterations = 8;
};
}  // namespace red