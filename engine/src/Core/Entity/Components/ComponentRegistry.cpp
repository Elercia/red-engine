#include "RedEngine/Core/Entity/Components/ComponentRegistry.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"

namespace red
{
std::pair<bool, ComponentTraits*> ComponentRegistry::CreateNewComponentTraits(TypeTraitsId componentId)
{
    auto* otherCompTraits = GetComponentTraitsInternal(componentId);

    if (otherCompTraits != nullptr)
    {
        return {false, otherCompTraits};
    }

    m_componentDatas.insert({componentId, ComponentTraits()});

    return {true, &m_componentDatas[componentId]};
}

const ComponentTraits* ComponentRegistry::GetComponentTraits(TypeTraitsId componentId) const
{
    auto foundIt = m_componentDatas.find(componentId);
    if (foundIt == m_componentDatas.end())
    {
        return nullptr;
    }

    return &foundIt->second;
}

ComponentTraits* ComponentRegistry::GetComponentTraitsInternal(TypeTraitsId componentId)
{
    auto foundIt = m_componentDatas.find(componentId);
    if (foundIt == m_componentDatas.end())
    {
        return nullptr;
    }

    return &foundIt->second;
}
}  // namespace red