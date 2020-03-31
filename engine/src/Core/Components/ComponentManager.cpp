#include "RedEngine/Core/Components/ComponentManager.hpp"

namespace red
{
ComponentManager::ComponentManager() : m_components() {}

std::set<Component*> ComponentManager::GetComponents(Entity* entity) { return {}; }
}  // namespace red
