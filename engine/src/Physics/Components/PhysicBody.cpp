#include <RedEngine/Physics/Components/PhysicBody.hpp>
#include <RedEngine/Core/Entity/Entity.hpp>
#include <RedEngine/Physics/Components/Collider.hpp>

namespace red
{
PhysicBody::PhysicBody(Entity* entity, const PhysicBodyCreationDesc& desc)
    : Component(entity), m_desc(desc), m_body(nullptr)
{
}

PhysicBody::~PhysicBody() {}

b2Body* PhysicBody::GetBody() { return m_body; }

}  // namespace red
