#pragma once

#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/RedEngineBase.hpp"

namespace red
{
class SpriteAnimationSystem : public System
{
public:
    explicit SpriteAnimationSystem(World* world);

    void Update() override;

    void Finalise() override;
};

}  // namespace red