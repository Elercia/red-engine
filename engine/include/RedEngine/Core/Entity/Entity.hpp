#pragma once

#include <string>
#include <set>
#include <vector>

#include "../Components/Component.hpp"

namespace red
{
class World;

class Entity
{
public:
    Entity(World* world, EntityId_t id, std::string  name);
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

    std::set<Component*> GetComponents();

    template <typename T>
    bool HasComponent();

    [[nodiscard]] EntityId_t GetId() const;
    void SetId(EntityId_t id);

    void Destroy(); // TODO Make something of it

    void SetPersistent(bool persistent);

    void SetParent(Entity* parent);
    void AddChild(Entity* child);
    void RemoveChild(Entity* child);

protected:
    World* m_world;
    EntityId_t m_id;
    std::string m_name;

    bool m_isPersistent;

    Entity* m_parent;
    std::vector<Entity*> m_children;

};

}  // namespace red

#include "inl/Entity.inl"
