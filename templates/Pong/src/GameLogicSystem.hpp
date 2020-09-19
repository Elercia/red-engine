#pragma once

#include <RedEngine/Core/Entity/System.hpp>
#include <RedEngine/Core/Components/Transform.hpp>
#include <RedEngine/Math/Vector.hpp>

namespace red
{
struct WindowInfo;
}

class BallComponent;

class GameLogicSystem : public red::System
{
public:
    GameLogicSystem(red::World* world, red::Entity* paddleOne, red::Entity* paddleTwo,
                    red::Entity* ball);

    void Update() override;
    void Init() override;

    void CheckPoints(red::Vector2& vector2);

private:
    red::Entity *m_paddleOne, *m_paddleTwo, *m_ball;
};
