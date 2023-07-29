#pragma once

#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Rendering/Component/Sprite.hpp"

namespace red
{
class CameraComponent;
class Renderer;

class SpriteAnimationSystem : public System<QueryGroup<QueryRW<Sprite>>>
{
public:
    explicit SpriteAnimationSystem(World* world);
    virtual ~SpriteAnimationSystem() = default;

    virtual void Update() override;
};

}  // namespace red
