#pragma once

#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"

#include <array>

namespace red
{
class EventSystem : public System<SinglQuery<QueryRW<EventsComponent>>>
{
public:
    EventSystem(World* world);
    virtual ~EventSystem() = default;

    virtual void Init() override;
    virtual void Update() override;
};
}  // namespace red
