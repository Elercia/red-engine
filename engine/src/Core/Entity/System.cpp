#include "RedEngine/Core/Entity/System.hpp"

namespace red
{
System::System(World* world) : m_world(world) {}

Entity& System::GetSingletonEntity() { return m_world->GetSingletonEntity(); }

}  // namespace red
