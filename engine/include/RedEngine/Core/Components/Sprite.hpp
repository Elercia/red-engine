#pragma once

#include <RedEngine/RedEngineBase.hpp>

#include <string>
#include <vector>
#include <memory>
#include <SDL2/SDL_render.h>

#include "../../Math/Vector.hpp"
#include "Component.hpp"
#include <RedEngine/Resources/AnnimationDescriptor.hpp>

namespace red
{
class Texture2D;

class Sprite : public Component
{
    friend class RenderingEngine;
    friend class ResourceEngine;

public:
    Sprite(Entity* entity, const std::string& resourceId);

    /// Compute the modifications to do for the next frame
    void NextFrame();

    /// Start a new animation by it first frame
    /// name : The animation name
    /// 
    /// Return true if the animation is found false otherwise
    bool StartAnimation(const std::string& name);

	std::vector<AnimationDesc> GetAnimations() const;

	CurrentAnimationDesc GetCurrentAnimationInfo() const;

    private:
    std::vector<AnimationDesc> m_animations;
    CurrentAnimationDesc m_currentAnimationInfo;

};
}  // namespace red
