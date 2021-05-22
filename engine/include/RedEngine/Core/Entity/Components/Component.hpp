#pragma once

#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Utils/Uncopyable.hpp"
#include "RedEngine/Core/Entity/Components/ComponentRegistry.hpp"
#include "RedEngine/Core/Entity/Components/ComponentRegistryFunction.hpp"

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
    RED_START_COMPONENT_REGISTER(Component)
    RED_END_COMPONENT_REGISTER()

    explicit Component(Entity* entity);
    virtual ~Component() = default;

    Component(Component&&) = default;
    Component& operator=(Component&&) = default;

    [[nodiscard]] Entity* GetOwner() const;

    virtual void Serialize() const;
    virtual void Deserialize();

protected:
    Entity* m_owner;
    ComponentStatus m_status;
};

}  // namespace red
