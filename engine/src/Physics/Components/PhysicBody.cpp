#include "RedEngine/Physics/PhysicsModule.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"

#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Physics/Components/Collider.hpp"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(PhysicBody)

PhysicBody::PhysicBody(Entity* entity) : Component(entity), m_desc(), m_body(nullptr)
{
}

PhysicBody::PhysicBody(Entity* entity, const PhysicBodyCreationDesc& desc)
    : Component(entity), m_desc(desc), m_body(nullptr)
{
}

PhysicBody::~PhysicBody() {}

void PhysicBody::ApplyForce(const Vector2& force, const Vector2& relativePosition)
{
    auto worldPosition = ConvertFromPhysicsVector(m_body->GetPosition()) + relativePosition;

    m_body->ApplyForce(ConvertToPhysicsVector(force), ConvertToPhysicsVector(worldPosition), true);
}

b2Body* PhysicBody::GetBody() { return m_body; }

void PhysicBody::SetBody(b2Body* body)
{
    m_body = body;
}
}  // namespace red
