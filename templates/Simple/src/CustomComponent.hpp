#pragma once

#include <RedEngine/ecs/Component.hpp>

class CustomComponent : public red::Component
{
public:
    RED_COMPONENT('CUST')

    CustomComponent(red::Entity* entity) : Component(entity)
    {}
};
