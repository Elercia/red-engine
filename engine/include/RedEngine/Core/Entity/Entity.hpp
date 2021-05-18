#pragma once

#include "RedEngine/Core/Components/Component.hpp"
#include "RedEngine/Core/Components/ComponentManager.hpp"
#include "RedEngine/Core/Components/Transform.hpp"
#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Utils/TypesInfo.hpp"

#include <algorithm>
#include <cassert>
#include <set>
#include <string>
#include <vector>

namespace red
{
using EntityId = uint32;

class World;

class Entity
{
    friend World;

public:
    Entity(World* world, EntityId id, std::string name);
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

    [[nodiscard]] EntityId GetId() const;
    [[nodiscard]] bool IsRootEntity() const;
    void SetId(EntityId id);

    const std::string& GetName() const;

    void Destroy();

    void SetPersistent(bool persistent);

    void SetParent(Entity* parent);
    void AddChild(Entity* child);
    void RemoveChild(Entity* child);
    Entity* GetParent();
    std::vector<Entity*> GetChildren();

    World* GetWorld();

    ComponentManager* GetComponentManager();

protected:
    World* m_world;
    EntityId m_id;
    std::string m_name;

    bool m_isPersistent;

    Entity* m_parent;
    std::vector<Entity*> m_children;
    bool m_isDirty{false};  // TODO Look at how to set it back to non-dirty
    bool m_isDestroyed{false};
};

}  // namespace red

#include "inl/Entity.inl"
