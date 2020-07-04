#pragma once

#include <RedEngine/Core/Components/Component.hpp>
#include <RedEngine/Math/Vector.hpp>

#include <utility>

class BallComponent : public red::Component
{
    friend class GameLogicSystem;

public:
    BallComponent(red::Entity* entity, const red::Vector2& initialVelocity)
        : red::Component(entity), m_velocity(std::move(initialVelocity)){};

private:
    red::Vector2 m_velocity;
};
