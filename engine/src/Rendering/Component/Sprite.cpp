#include "RedEngine/Rendering/Component/Sprite.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Core/Time/Time.hpp"
#include "RedEngine/Rendering/Resource/GeometryResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/MaterialResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/SpriteResourceLoader.hpp"
#include "RedEngine/Resources/ResourceHolderComponent.hpp"

#include <utility>

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(Sprite)

Sprite::Sprite(Entity* entity) : Renderable(entity), m_spriteResource(nullptr)
{
}

Sprite::Sprite(Entity* entity, const Path& resourceId) : Renderable(entity)
{
    m_spriteResource = m_owner->GetWorld()
                           ->GetWorldComponent<ResourceHolderComponent>()
                           ->GetResourceLoader<SpriteResourceLoader>()
                           ->LoadResource(resourceId);

    m_material.material = m_owner->GetWorld()
                        ->GetWorldComponent<ResourceHolderComponent>()
                        ->GetResourceLoader<MaterialResourceLoader>()
                       ->LoadResource(Path::Resource("BASE_MATERIAL"));
    m_geometry = m_owner->GetWorld()
                        ->GetWorldComponent<ResourceHolderComponent>()
                        ->GetResourceLoader<GeometryResourceLoader>()
                       ->LoadResource(Path::Resource("BASE_GEOMETRY"));

    if (m_spriteResource)
    {
        m_currentAnimationInfo.currentAnimation = m_spriteResource->m_animations.begin();
        m_currentAnimationInfo.currentAnimationFrame = m_spriteResource->m_animations[0].frames.begin();
        m_currentAnimationInfo.deltaTimeAccumulator = 0;
    }
}

void Sprite::NextFrame()
{
    m_currentAnimationInfo.deltaTimeAccumulator += Time::DeltaTime();

    auto duration = m_currentAnimationInfo.currentAnimationFrame->duration;

    // If the frame is not infinite and the frame duration is passed
    if (duration > 0 && duration <= m_currentAnimationInfo.deltaTimeAccumulator)
    {
        // reset the accumulator and change the current animation
        m_currentAnimationInfo.deltaTimeAccumulator = 0;

        m_currentAnimationInfo.currentAnimationFrame++;

        // We are at the end of the frame list, stop here if the animation is not a loop
        if (m_currentAnimationInfo.currentAnimationFrame == m_currentAnimationInfo.currentAnimation->frames.end())
        {
            if (m_currentAnimationInfo.currentAnimation->loop)
            {
                m_currentAnimationInfo.currentAnimationFrame = m_currentAnimationInfo.currentAnimation->frames.begin();
            }
            else
            {
                m_currentAnimationInfo.currentAnimationFrame--;
            }
        }
    }

    UpdateRenderData();
}

bool Sprite::StartAnimation(const std::string& name)
{
    if (!m_spriteResource)
        return false;

    for (auto it = m_spriteResource->m_animations.begin(); it != m_spriteResource->m_animations.end(); it++)
    {
        if (it->name == name)
        {
            m_currentAnimationInfo.currentAnimation = it;
            m_currentAnimationInfo.currentAnimationFrame = it->frames.begin();
            m_currentAnimationInfo.deltaTimeAccumulator = 0;
            return true;
        }
    }

    return false;
}

const Array<AnimationDesc>& Sprite::GetAnimations() const
{
    return m_spriteResource->m_animations;
}

const CurrentAnimationDesc& Sprite::GetCurrentAnimationInfo() const
{
    return m_currentAnimationInfo;
}

bool Sprite::IsValid() const
{
    return m_material.material != nullptr && m_geometry != nullptr && m_spriteResource != nullptr && m_spriteResource->GetLoadState() == LoadState::STATE_LOADED;
}

void Sprite::UpdateRenderData()
{
    m_material.parameters.parameters["texture_sampler"].texture = m_currentAnimationInfo.currentAnimation->texture;
    m_material.parameters.parameters["texture_sampler"].type = ValueType::TEXTURE;

    const Vector2i& sizei = m_currentAnimationInfo.currentAnimationFrame->size;
    m_size = {(float)sizei.x, (float)sizei.y};
}

}  // namespace red