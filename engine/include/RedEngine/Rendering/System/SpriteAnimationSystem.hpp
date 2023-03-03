#pragma once

#include "RedEngine/Core/Entity/System.hpp"

namespace red
{
class CameraComponent;
class Renderer;

class SpriteAnimationSystem : public System
{
public:
    explicit SpriteAnimationSystem(World* world);
    virtual ~SpriteAnimationSystem() = default;

    virtual void Update() override;
};

}  // namespace red
