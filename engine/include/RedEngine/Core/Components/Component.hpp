#pragma once

#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Utils/Uncopyable.hpp"

#include <memory>

namespace red
{
class Entity;

using ComponentId = uint32_t;

enum class ComponentStatus
{
    CREATED,
    DIRTY,
    VALID
};

class Component : public Uncopyable
{
public:
    explicit Component(Entity* entity);
    virtual ~Component() = default;

    Component(Component&&) = default;
    Component& operator=(Component&&) = default;

    [[nodiscard]] Entity* GetOwner() const;

protected:
    Entity* m_owner;
    ComponentStatus m_status;
};

}  // namespace red
