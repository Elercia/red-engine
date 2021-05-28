#pragma once

#include "RedEngine/Core//Container/Map.hpp"
#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Utils/Types.hpp"

#include <functional>
#include <string_view>
#include <variant>

namespace red
{
class Component;

enum class ComponentMemberFlag
{
    READ_ONLY = 1 << 0,
    READ_WRITE = 1 << 1,
    NO_SERIALIZE = 1 << 2,
    NONE = READ_WRITE,  // Default to read-write
};

struct ComponentMemberData
{
    std::string name;
    std::string tooltip;
    uint32 flags;

    std::function<std::string(const Component* /*comp*/)> serializationFunction;
    std::function<void(Component* /*comp*/, const std::string& /*serializedData*/)> deserializationFunction;
};

struct ComponentData
{
    std::string_view componentName;
    std::string_view inheritedComponentName;
    Map<std::string, ComponentMemberData> members;

    template <typename ComponentTypeT, typename MemberTypeT>
    void AddMember(const std::string& name, MemberTypeT ComponentTypeT::*memberAddr, const std::string& tooltip,
                   uint32 flags);
};

class ComponentRegistry
{
public:
    ComponentRegistry() = default;
    ~ComponentRegistry() = default;

    ComponentData* CreateNewComponentData(const std::string& componentName);

    ComponentData* GetComponentData(const std::string& componentName);

private:
    Map<std::string, ComponentData> m_componentDatas;
};
}  // namespace red

#include "inl/ComponentRegistry.inl"