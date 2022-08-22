#pragma once

#include "RedEngine/Core/Entity/Components/Component.hpp"

class ScoreComponent;

RED_COMPONENT_BASIC_FUNCTIONS_DECLARATION(ScoreComponent)

class ScoreComponent : public red::Component
{
    friend class GameLogicSystem;

public:
    explicit ScoreComponent(red::Entity* entity) : red::Component(entity) {}
    ~ScoreComponent() override = default;

    RED_START_COMPONENT_REGISTER_INHERITHED(ScoreComponent, Component)
    RED_END_COMPONENT_REGISTER()

private:
    std::pair<int, int> m_scores{0, 0};
};