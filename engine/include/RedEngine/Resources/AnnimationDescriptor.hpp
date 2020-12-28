#pragma once

#include <RedEngine/RedEngineBase.hpp>
#include "RedEngine/Math/Vector.hpp"

#include <vector>
#include <memory>

namespace red
{
class Texture2D;

struct AnimationFrameDesc
{
    float duration{0};  ///< The duration of the animation (in millis)
    Vector4i rect;      ///< The rect used to crop the animation inside the m_texture
    Vector2i size;      ///< The height and width used to resize the sprite to the wanted dimension
    Vector2i center;    ///< The center of the animation frame (according to the given "size")
    bool flipV{false};
    bool flipH{false};
    double rotation{0.F};  ///< Rotation in degree (clockwise)
};

struct AnimationDesc
{
    std::string name;
    bool loop{false};
    std::shared_ptr<Texture2D> texture; ///< The animation spritesheet
    std::vector<AnimationFrameDesc> frames;
};

struct CurrentAnimationDesc
{
    float deltaTimeAccumulator{0};
    std::vector<AnimationDesc>::iterator currentAnimation;
    std::vector<AnimationFrameDesc>::iterator currentAnimationFrame;
};
}