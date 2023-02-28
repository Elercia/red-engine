#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Rendering/Component/Renderable.hpp"
#include "RedEngine/Resources/AnnimationDescriptor.hpp"

#include <memory>
#include <string>

namespace red
{
class SpriteResource;

class Sprite : public Component
{
    friend class Renderer;

public:
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

    MaterialInstance& GetMaterial();
    const MaterialInstance& GetMaterial() const;
    std::shared_ptr<GeometryResourceWrapper> GetGeometry();

    void SetRenderLayerIndex(RenderLayerIndex layerIndex);
    RenderLayerIndex GetRenderLayerIndex() const;

    bool IsValid() const;

    friend void RegisterMembers<Sprite>(ComponentTraits& traits);

private:
    void UpdateRenderData();

private:
    RenderLayerIndex m_layerIndex;
    Vector2 m_size;
    AABB m_aabb;
    std::shared_ptr<GeometryResourceWrapper> m_geometry;
    MaterialInstance m_material;
    std::shared_ptr<SpriteResource> m_spriteResource;
    CurrentAnimationDesc m_currentAnimationInfo;
};
}  // namespace red
