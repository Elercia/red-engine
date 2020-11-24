#pragma once

#include <RedEngine/RedEngineBase.hpp>

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

struct PhysicBodyCreationDesc
{
    PhysicsBodyType type;
};

class PhysicBody : public Component
{
    friend class PhysicSystem;

public:
    PhysicBody(Entity* entity, const PhysicBodyCreationDesc& desc);
    ~PhysicBody();

    void SetFastObject(bool fast);
    void SetActive(bool active);

    b2Body* GetBody();

private:
    PhysicBodyCreationDesc m_desc;
    b2Body* m_body;
};
}  // namespace red