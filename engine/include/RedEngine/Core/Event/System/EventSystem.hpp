#pragma once

#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/RedEngineBase.hpp"

#include <array>

namespace red
{
class EventSystem : public System
{
public:
    EventSystem(World* world);
    virtual ~EventSystem() = default;

    virtual void Init() override;

    virtual void PreUpdate() override;
    virtual void PostUpdate() override;
};
}  // namespace red
