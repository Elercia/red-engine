#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Entity/CommonEntityTypes.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/Entity/Components/ComponentManager.hpp"

#include <string>

namespace red
{

class World;
class Transform;

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

    Entity(Entity&&) = delete;
    Entity& operator=(Entity&& entity) = delete;

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

    [[nodiscard]] EntityId GetId() const;
    void SetId(EntityId id);

    const std::string GetFullName() const;
    const std::string& GetName() const;
    void SetName(const std::string& name);

    EntityState GetState() const;

    void Destroy();

    void SetParent(Entity* parent);
    void AddChild(Entity* child);
    void RemoveChild(Entity* child);
    Entity* GetParent();
    const Entity* GetParent() const;
    const Array<Entity*>& GetChildren() const;

    World* GetWorld();

    ComponentManager* GetComponentManager();

protected:
    World* m_world{nullptr};
    EntityId m_id{0};
    Transform* m_transform;
    std::string m_name;

    Entity* m_parent{nullptr};
    Array<Entity*> m_children;
    EntityState m_state{EntityState::PreCreation};
};

}  // namespace red

#include "inl/Entity.inl"
