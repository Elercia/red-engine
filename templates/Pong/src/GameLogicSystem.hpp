#pragma once

#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"

#include "ScoreComponent.hpp"

namespace red
{
struct WindowInfo;
}

class BallComponent;

class GameLogicSystem : public red::System<red::QueryGroup<red::QueryRW<ScoreComponent>>>
{
public:
    GameLogicSystem(red::World* world, red::Entity* paddleOne, red::Entity* paddleTwo, red::Entity* ball);

    void Update() override;
    void Init() override;

    void CheckPoints(red::Vector2& vector2);

    red::Entity *m_paddleOne, *m_paddleTwo, *m_ball;
    red::PhysicBody::OnCollisionSignalType::Slot m_paddlecollisionSignal;
};
