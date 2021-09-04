#include "RedEngine/Core/Entity/Components/ComponentRegistry.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"

namespace red
{
ComponentTraits* ComponentRegistry::CreateNewComponentTraits(const std::string& componentName)
{
    if (GetComponentTraits(componentName) != nullptr)
    {
        RED_LOG_ERROR("ComponentRegistry already have registered a component named {}", componentName);
        RED_ABORT("ComponentRegistry CreateNewComponentData failed");
    }

    m_componentDatas.insert(std::make_pair(componentName, ComponentTraits()));

    return &m_componentDatas[componentName];
}

const ComponentTraits* ComponentRegistry::GetComponentTraits(const std::string& componentName) const
{
    auto foundIt = m_componentDatas.find(componentName);
    if (foundIt == m_componentDatas.end())
    {
        return nullptr;
    }

    return &foundIt->second;
}

}  // namespace red