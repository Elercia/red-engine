#pragma once

#include <RedEngine/RedEngineBase.hpp>

#include <memory>

#include "../EngineConfig.hpp"

namespace red
{
class Entity;

enum class ComponentStatus
{
    CREATED,
    DIRTY,
    VALID
};

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

protected:
    ComponentId_t m_componentId;
    Entity* m_owner;
    ComponentStatus m_status;

};

}  // namespace red
