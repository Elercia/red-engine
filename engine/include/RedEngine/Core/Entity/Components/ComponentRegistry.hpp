#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Utils/Types.hpp"

#include <string_view>
#include <variant>

namespace red
{
struct ComponentMemberData
{
};

struct ComponentData
{
    std::string_view componentName;
    std::string_view inheritedComponentName;
    Array<ComponentMemberData> members;
};

class ComponentRegistry
{
public:
    ComponentRegistry() = default;
    ~ComponentRegistry() = default;

    ComponentData* CreateNewComponentData();

private:
    Array<ComponentData> m_componentDatas;
};
}  // namespace red

#include "inl/ComponentRegistry.inl"