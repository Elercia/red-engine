#pragma once

#include "RedEngine/Core//Container/Map.hpp"
#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Utils/Types.hpp"

#include <functional>
#include <variant>

namespace red
{
class Component;
class Entity;

enum class ComponentMemberFlag
{
    READ_ONLY = 1 << 0,
    READ_WRITE = 1 << 1,
    NO_SERIALIZE = 1 << 2,
    NONE = READ_WRITE,  // Default to read-write
};

struct ComponentMemberTraits
{
    std::string name;
    std::string tooltip;
    uint32 flags;

    // Serialize the member for the given component
    std::function<std::string(const Component* /*comp*/)> serializationFunction;
    std::function<void(Component* /*comp*/, const std::string& /*serializedData*/)> deserializationFunction;
};

struct ComponentTraits
{
    std::string_view componentName;
    uint32 componentTypeId;
    std::string_view inheritedComponentName;
    Array<ComponentTraits*> childComponentTraits;
    Map<std::string, ComponentMemberTraits> members; // member name to Traits
    std::function<Component*(Entity* owner)> creator;

    template <typename ComponentTypeT, typename MemberTypeT>
    void AddMember(const std::string& name, MemberTypeT ComponentTypeT::*memberAddr, const std::string& tooltip,
                   uint32 flags);
};

class ComponentRegistry
{
    friend class World;

public:
    ComponentRegistry() = default;
    ~ComponentRegistry() = default;

    std::pair<bool, ComponentTraits*> CreateNewComponentTraits(const std::string& componentName);

    const ComponentTraits* GetComponentTraits(const std::string& componentName) const;

private:
    ComponentTraits* GetComponentTraitsInternal(const std::string& componentName);

private:
    Map<std::string, ComponentTraits> m_componentDatas;
};
}  // namespace red

#include "inl/ComponentRegistry.inl"