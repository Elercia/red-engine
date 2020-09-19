#include <RedEngine/Core/Components/Sprite.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>
#include <RedEngine/Core/Time/Time.hpp>

#include <utility>

namespace red
{
Sprite::Sprite(Entity* entity, const std::string& resourceId) : Component(entity)
{
    ResourceEngine::LoadSprite(resourceId, this);
    m_currentAnimationInfo.currentAnimation = m_animations.begin();
    m_currentAnimationInfo.currentAnimationFrame = m_animations[0].frames.begin();
    m_currentAnimationInfo.deltaTimeAccumulator = 0;
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
        if (m_currentAnimationInfo.currentAnimationFrame ==
            m_currentAnimationInfo.currentAnimation->frames.end())
        {
            if (m_currentAnimationInfo.currentAnimation->loop)
            {
                m_currentAnimationInfo.currentAnimationFrame =
                    m_currentAnimationInfo.currentAnimation->frames.begin();
            }
            else
            {
                m_currentAnimationInfo.currentAnimationFrame--;
            }
        }
    }
}

bool Sprite::StartAnimation(const std::string& name)
{
    for (auto it = m_animations.begin(); it != m_animations.end(); it++)
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

std::vector<AnimationDesc> Sprite::GetAnimations() const { return m_animations; }

CurrentAnimationDesc Sprite::GetCurrentAnimationInfo() const { return m_currentAnimationInfo; }

}  // namespace red