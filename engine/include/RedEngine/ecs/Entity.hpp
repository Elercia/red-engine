#pragma once

#include <RedEngine/ecs/Component.hpp>

#include <memory>
#include <optional>
#include <set> // TODO change for better performance

namespace red
{
class World;

class Entity
{
public:
    explicit Entity(World* world, EntityId_t id);
    virtual ~Entity() = default;

    Entity(const Entity&) = delete;
    Entity(Entity&&) = default;

    Entity& operator=(const Entity& entity) = delete;
    Entity& operator=(Entity&& entity) = default;

    template <typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args);

    template <typename T>
    void RemoveComponent();

    template <typename T>
    std::shared_ptr<T> GetComponent();

    std::set<std::shared_ptr<Component>>& GetComponents();

    template <typename T>
    bool HasComponent();

    [[nodiscard]] EntityId_t GetId() const;

    void Destroy();

protected:
    std::set<std::shared_ptr<Component>> m_components;
    World* m_world;
    EntityId_t m_id;
};

} // namespace red

#include "inl/Entity.inl"
