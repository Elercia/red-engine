#pragma once

#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Math/Vector.hpp"

class GameControlSystem : public red::System
{
public:
    GameControlSystem(red::World* world, red::Entity* paddleOne, red::Entity* paddleTwo);
    ~GameControlSystem() override = default;

    void Update() override;

    void KeepInBound(red::Vector2& pos);

private:
    red::Entity* m_paddleOne;
    red::Entity* m_paddleTwo;
};