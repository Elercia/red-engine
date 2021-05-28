#pragma once

#include "RedEngine/Core/Entity/Components/ComponentRegistry.hpp"
#include "RedEngine/Core/Entity/Components/ComponentRegistryFunction.hpp"
#include "RedEngine/Core/SerializationFunction.hpp"
#include "RedEngine/Math/SerializationFunction.hpp"
#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Utils/Uncopyable.hpp"

#include <memory>

namespace red
{
class Entity;
class World;
class ILevelComponentData;

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
    [[nodiscard]] World* GetWorld() const;

    void Serialize(ILevelComponentData* levelComponentData) const;
    void Deserialize(const ILevelComponentData* levelComponentData);

protected:
    Entity* m_owner;
    ComponentStatus m_status;
};

}  // namespace red
