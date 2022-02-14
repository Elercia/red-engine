#include "RedEngine/Core/Entity/Components/ComponentRegistry.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"

namespace red
{
std::pair<bool, ComponentTraits*> ComponentRegistry::CreateNewComponentTraits(const std::string& componentName)
{
    auto* otherCompTraits = GetComponentTraitsInternal(componentName);

    if (otherCompTraits != nullptr)
    {
        RED_LOG_ERROR("ComponentRegistry already have registered a component named {}", componentName);
        return {false, otherCompTraits};
    }

    m_componentDatas.insert({componentName, ComponentTraits()});

    return {true, &m_componentDatas[componentName]};
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

ComponentTraits* ComponentRegistry::GetComponentTraitsInternal(const std::string& componentName)
{
    auto foundIt = m_componentDatas.find(componentName);
    if (foundIt == m_componentDatas.end())
    {
        return nullptr;
    }

    return &foundIt->second;
}
}  // namespace red