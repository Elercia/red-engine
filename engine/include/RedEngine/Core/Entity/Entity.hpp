#pragma once

#include <RedEngine/RedEngineBase.hpp>

#include <string>
#include <set>
#include <vector>

#include "../Components/Component.hpp"

namespace red
{
class World;

class Entity
{
    friend World;

public:
    Entity(World* world, EntityId_t id, std::string name);
    virtual ~Entity() = default;

    Entity(const Entity&) = delete;
    Entity& operator=(const Entity& entity) = delete;

    Entity(Entity&&) = default;
    Entity& operator=(Entity&& entity) = default;

    template <typename T, typename... Args>
    T* AddComponent(Args&&... args);

    template <typename T>
    void RemoveComponent();

    template <typename T>
    T* GetComponent();

    template <typename T>
    T* GetComponentInParent(bool includeOwn = true);

    std::set<Component*> GetComponents();

    template <typename T>
    bool HasComponent();

    [[nodiscard]] EntityId_t GetId() const;
    [[nodiscard]] bool IsRootEntity() const;
    void SetId(EntityId_t id);

    const std::string& GetName() const;

    void Destroy();

    void SetPersistent(bool persistent);

    void SetParent(Entity* parent);
    void AddChild(Entity* child);
    void RemoveChild(Entity* child);
    Entity* GetParent();
    std::vector<Entity*> GetChildren();

    World* GetWorld();

protected:
    World* m_world;
    EntityId_t m_id;
    std::string m_name;

    bool m_isPersistent;

    Entity* m_parent;
    std::vector<Entity*> m_children;
    bool m_isDirty{false};  // TODO Look at how to set it back to non-dirty
    bool m_isDestroyed{false};
};

}  // namespace red

#include "inl/Entity.inl"
