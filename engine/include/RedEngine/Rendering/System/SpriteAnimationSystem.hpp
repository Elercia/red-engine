#pragma once

#include <RedEngine/RedEngineBase.hpp>

#include <RedEngine/Core/Entity/System.hpp>

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