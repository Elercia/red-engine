#include "RedEngine/Rendering/Component/Sprite.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Core/Time/Time.hpp"
#include "RedEngine/Rendering/Resource/GeometryResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/Material.hpp"
#include "RedEngine/Rendering/Resource/MaterialResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/SpriteResourceLoader.hpp"
#include "RedEngine/Resources/ResourceHolderComponent.hpp"

#include <utility>

namespace red
{
template <>
inline void RegisterMembers<Sprite>(ComponentTraits& traits)
{
    traits.AddMember("Layer index", &Sprite::m_layerIndex, "The layer of the object", 0);
    traits.AddMember("Size of the sprite", &Sprite::m_size, "The layer of the object", 0);
    // traits.AddMember("Sprite resource", &Sprite::m_spriteResource, "The layer of the object", 0);
}

Sprite::Sprite(Entity* entity) : Component(entity), m_spriteResource(nullptr)
{
    m_owner->AddComponent<Renderable>();
}

Sprite::Sprite(Entity* entity, const Path& resourceId) : Component(entity)
{
    m_owner->AddComponent<Renderable>();

    m_spriteResource = m_owner->GetWorld()
                           ->GetWorldComponent<ResourceHolderComponent>()
                           ->GetResourceLoader<SpriteResourceLoader>()
                           ->LoadResource(resourceId);

    m_geometry = m_owner->GetWorld()
                     ->GetWorldComponent<ResourceHolderComponent>()
                     ->GetResourceLoader<GeometryResourceLoader>()
                     ->LoadResource(Path::Resource("ENGINE_RESOURCES/SPRITE_GEOMETRY"));

    if (m_spriteResource->GetLoadState() == LoadState::STATE_LOADED)
    {
        m_currentAnimationInfo.currentAnimation = m_spriteResource->m_animations.begin();
        m_currentAnimationInfo.currentAnimationFrame = m_spriteResource->m_animations[0].frames.begin();
        m_currentAnimationInfo.deltaTimeAccumulator = 0;

        m_material.material = m_currentAnimationInfo.currentAnimation->material;
    }
}

void Sprite::NextFrame()
{
    if (m_spriteResource->GetLoadState() != LoadState::STATE_LOADED)
        return;

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
    if (m_spriteResource->GetLoadState() != LoadState::STATE_LOADED)
    {
        auto* renderable = m_owner->GetComponent<Renderable>();
        renderable->Hide();

        return false;
    }

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
    return m_material.material != nullptr && m_geometry != nullptr && m_spriteResource != nullptr &&
           m_spriteResource->GetLoadState() == LoadState::STATE_LOADED;
}

void Sprite::UpdateRenderData()
{
    auto& binding = m_material.overriddenBindings.bindings[BindingIndex::Diffuse];
    binding.texture = m_currentAnimationInfo.currentAnimation->texture.get();
    binding.type = BindingType::Texture;

    m_material.material = m_currentAnimationInfo.currentAnimation->material;

    const Vector2i& sizei = m_currentAnimationInfo.currentAnimationFrame->size;

    m_size = Vector2((float) sizei.x, (float) sizei.y) * GetOwner()->GetComponent<Transform>()->GetScale();

    m_aabb = AABB(GetOwner()->GetComponent<Transform>()->GetLocalPosition(), m_size);  // * scale

    auto* renderable = m_owner->GetComponent<Renderable>();

    renderable->Show();
    renderable->SetRenderLayerIndex(m_layerIndex);
    renderable->SetSize(m_size);
    renderable->SetAABB(m_aabb);
    renderable->SetGeometry(m_geometry);
    renderable->SetMaterialInstance(m_material);
}

MaterialInstance& Sprite::GetMaterial()
{
    return m_material;
}

const MaterialInstance& Sprite::GetMaterial() const
{
    return m_material;
}

std::shared_ptr<GeometryResourceWrapper> Sprite::GetGeometry()
{
    return m_geometry;
}

void Sprite::SetRenderLayerIndex(RenderLayerIndex layerIndex)
{
    m_layerIndex = layerIndex;
}

RenderLayerIndex Sprite::GetRenderLayerIndex() const
{
    return m_layerIndex;
}

}  // namespace red