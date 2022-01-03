#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Entity/CommonEntityTypes.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/Entity/Components/ComponentManager.hpp"

#include <string>

namespace red
{

class World;

enum class EntityState
{
    PreCreation,
    Created,
    Destroyed
};

class Entity
{
    friend World;

public:
    Entity(World* world, EntityId id);
    virtual ~Entity() = default;

    Entity(const Entity&) = delete;
    Entity& operator=(const Entity& entity) = delete;

    Entity(Entity&&) = default;
    Entity& operator=(Entity&& entity) = default;

    template <typename T, typename... Args>
    T* AddComponent(Args&&... args);

    Component* AddComponent(const std::string& name);

    template <typename T>
    bool RemoveComponent();

    template <typename T>
    T* GetComponent();

    template <typename T>
    T* GetComponentInParent(bool includeOwn = true);

    Array<Component*> GetComponents() const;

    template <typename T>
    bool HasComponent();

    [[nodiscard]] EntityId GetId() const;
    void SetId(EntityId id);

    const std::string& GetName() const;
    void SetName(const std::string& name);

    const EntityState GetState() const;

    void Destroy();

    void SetParent(Entity* parent);
    void AddChild(Entity* child);
    void RemoveChild(Entity* child);
    Entity* GetParent();
    const Entity* GetParent() const;
    Array<Entity*> GetChildren() const;

    World* GetWorld();

    ComponentManager* GetComponentManager();

protected:
    World* m_world;
    EntityId m_id;
    std::string m_name;

    Entity* m_parent;
    Array<Entity*> m_children;
    EntityState m_state;
};

}  // namespace red

#include "inl/Entity.inl"
