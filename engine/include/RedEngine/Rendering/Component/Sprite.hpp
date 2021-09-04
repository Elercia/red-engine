#pragma once

#include "RedEngine/Core/Components/Component.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Resources/AnnimationDescriptor.hpp"

#include <SDL2/SDL_render.h>
#include <memory>
#include <string>
#include <vector>

namespace red
{
class SpriteResource;

class Sprite : public Component
{
    friend class Renderer;

public:
    Sprite(Entity* entity, const Path& resourceId);

    /// Compute the modifications to do for the next frame
    void NextFrame();

    /// Start a new animation by it first frame
    /// name : The animation name
    ///
    /// Return true if the animation is found false otherwise
    bool StartAnimation(const std::string& name);

    const std::vector<AnimationDesc>& GetAnimations() const;

    const CurrentAnimationDesc& GetCurrentAnimationInfo() const;

    bool IsValid() const;

private:
    std::shared_ptr<SpriteResource> m_spriteResource;
    CurrentAnimationDesc m_currentAnimationInfo;
};
}  // namespace red
