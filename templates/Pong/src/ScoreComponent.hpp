#pragma once

#include <RedEngine/Core/Components/Component.hpp>

class ScoreComponent : public red::Component
{
    friend class GameLogicSystem;

public:
    explicit ScoreComponent(red::Entity* entity) : red::Component(entity) {}
    ~ScoreComponent() override = default;

private:
    std::pair<int, int> m_scores{0, 0};
};