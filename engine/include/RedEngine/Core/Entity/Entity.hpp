#pragma once

#include <memory>
#include <optional>
#include <set>

#include "../Components/Component.hpp"

namespace red
{
class World;

class Entity
{
public:
    Entity(World* world, EntityId_t id);
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

    void Destroy();

    void SetPersistent(bool persistent);

protected:
    World* m_world;
    EntityId_t m_id;
};

}  // namespace red

#include "inl/Entity.inl"
