#pragma once

#include "../EngineConfig.hpp"

#include <memory>

namespace red
{
class Entity;

// RED_COMPONENT
#define RED_COMPONENT(NAME)                                                                        \
public:                                                                                            \
    enum : red::ComponentName_t                                                                    \
    {                                                                                              \
        ComponentName = NAME                                                                       \
    };                                                                                             \
    virtual red::ComponentName_t (GetComponentName)() const                                          \
    {                                                                                              \
        return ComponentName;                                                                      \
    };
// RED_COMPONENT

class Component
{
    RED_COMPONENT('COMP')
public:
    Component(Entity* entity);
    Component(Component&&) = default;
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;
    Component& operator=(Component&&) = default;

    virtual ~Component() = default;

    ComponentName_t GetComponentId() const;

	[[nodiscard]] Entity* GetOwner() const;

protected:
    ComponentId_t m_componentId;
    Entity* m_owner;
};

} // namespace red
