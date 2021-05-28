#include "RedEngine/Core/Entity/Components/ComponentRegistry.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"

namespace red
{
ComponentData* ComponentRegistry::CreateNewComponentData(const std::string& componentName)
{
    if (GetComponentData(componentName) != nullptr)
    {
        RED_LOG_ERROR("ComponentRegistry already have registered a component named {}", componentName);
        RED_ABORT("ComponentRegistry CreateNewComponentData failed");
    }

    m_componentDatas.insert(std::make_pair(componentName, ComponentData()));

    return &m_componentDatas[componentName];
}

red::ComponentData* ComponentRegistry::GetComponentData(const std::string& componentName)
{
    auto foundIt = m_componentDatas.find(componentName);
    if (foundIt == m_componentDatas.end())
    {
        return nullptr;
    }

    return &foundIt->second;
}

}  // namespace red