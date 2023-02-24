#pragma once

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Rendering/Component/Renderable.hpp"
#include "RedEngine/Resources/AnnimationDescriptor.hpp"

#include <memory>
#include <string>
#include "RedEngine/Core/Container/Array.hpp"

namespace red
{
class SpriteResource;

RED_COMPONENT_BASIC_FUNCTIONS_DECLARATION(Sprite)

class Sprite : public Renderable
{
    friend class Renderer;

public:
    RED_START_COMPONENT_REGISTER_INHERITHED(Sprite, Renderable)
    RED_END_COMPONENT_REGISTER()

    Sprite(Entity* entity);
    Sprite(Entity* entity, const Path& resourceId);

    /// Compute the modifications to do for the next frame
    void NextFrame();

    /// Start a new animation by it first frame
    /// name : The animation name
    ///
    /// Return true if the animation is found false otherwise
    bool StartAnimation(const std::string& name);

    const Array<AnimationDesc>& GetAnimations() const;

    const CurrentAnimationDesc& GetCurrentAnimationInfo() const;

    bool IsValid() const;

private:
    void UpdateRenderData();

private:
    std::shared_ptr<SpriteResource> m_spriteResource;

    CurrentAnimationDesc m_currentAnimationInfo;
};
}  // namespace red
