#pragma once

#include "RedEngine/Core/Entity/Components/ComponentRegistry.hpp"
#include "RedEngine/Core/SerializationFunction.hpp"
#include "RedEngine/Math/SerializationFunction.hpp"
#include "RedEngine/Utils/Uncopyable.hpp"

#include <memory>

namespace red
{
class Entity;
class World;
class Component;
class ILevelComponentData;
class ComponentManager;

using ComponentId = uint32_t;

enum class ComponentStatus
{
    CREATED,
    DIRTY,
    VALID
};

template <typename T>
inline void RegisterMembers(ComponentTraits& traits);

class Component : public Uncopyable
{
    friend World;
    friend ComponentManager;

public:
    explicit Component(Entity* entity);
    ~Component() = default;

    Component(Component&&) = default;
    Component& operator=(Component&&) = default;

    [[nodiscard]] Entity* GetOwner() const;
    [[nodiscard]] TypeTraits GetTypeTraits() const;

    [[nodiscard]] World* GetWorld() const;

protected:
    Entity* m_owner;
    TypeTraits m_typeTraits;
    ComponentStatus m_status;
};

}  // namespace red

#include "inl/Component.inl"