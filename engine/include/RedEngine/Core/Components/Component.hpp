#pragma once

#include <memory>

#include "../EngineConfig.hpp"

namespace red
{
class Entity;

// RED_COMPONENT
#define RED_COMPONENT(NAME)                                                                   \
    friend class RenderingEngine;                                                             \
    friend class ResourceEngine;                                                              \
                                                                                              \
public:                                                                                       \
    constexpr static red::ComponentName_t ComponentName = NAME;                               \
    virtual red::ComponentName_t GetComponentName() const override { return ComponentName; }; \
                                                                                              \
private:
// RED_COMPONENT

class Component
{
public:
    explicit Component(Entity* entity);
    Component(Component&&) = default;
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;
    Component& operator=(Component&&) = default;

    virtual ~Component() = default;

    [[nodiscard]] ComponentId_t GetComponentId() const;

    [[nodiscard]] Entity* GetOwner() const;

    [[nodiscard]] virtual red::ComponentName_t GetComponentName() const = 0;

protected:
    ComponentId_t m_componentId;
    Entity* m_owner;
};

}  // namespace red
