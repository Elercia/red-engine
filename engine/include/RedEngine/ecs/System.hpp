#pragma once

#include "../EngineConfig.hpp"
#include <set>

namespace red
{
class Entity;
class ComponentManager;

class System
{
public:
    System(ComponentManager* componentManager);
    System(System&&) = default;
    System(const System&) = delete;
    virtual ~System() = default;

    System& operator=(const System&) = delete;
    System& operator=(System&&) = default;

    virtual void Update(float deltaTime) = 0;

    template <typename T>
    void RequireComponentType();

    void GetComponents();

private:
    std::set<ComponentName_t> m_requiredComponents;
    ComponentManager* m_componentManager;
};
} // namespace red

#include "inl/System.inl"
