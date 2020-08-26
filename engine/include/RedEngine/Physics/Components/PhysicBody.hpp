#pragma once

#include "RedEngine/Core/Components/Component.hpp"
#include "RedEngine/Core/Event/Signal.hpp"

#include <Box2D/Dynamics/b2Body.h>

#include <vector>

namespace red
{
class ColliderList;
struct Collider;

enum class PhysicsBodyType
{
    STATIC_BODY,
    DYNAMIC_BODY,
    KINEMATIC_BODY
};

struct PhysicBodyColliderHolder
{
    ColliderList* colliderList;
    red::Signal<Collider*>::Slot* addedSlot;
    red::Signal<Collider*>::Slot* RemovedSlot;
};

class PhysicBody : public Component
{
public:
    PhysicBody(Entity* entity, PhysicsBodyType bodyType = PhysicsBodyType::DYNAMIC_BODY);
    ~PhysicBody();

    void Finalize() override;

    void SetFastObject(bool fast);
    void SetActive(bool active);

    void AddCollider(ColliderList* colliderList);
    void RemoveCollider(ColliderList* colliderList);

    void OnColliderAdded(Collider* collider);
    void OnColliderRemoved(Collider* collider);

    b2Body* GetBody();

private:
    b2Body* m_body;
    std::vector<PhysicBodyColliderHolder> m_colliders;
};
}  // namespace red