#pragma once

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Math/AABB.hpp"
#include "RedEngine/Rendering/Resource/Geometry.hpp"
#include "RedEngine/Rendering/Resource/Material.hpp"

namespace red
{
class Renderable;

using RenderLayerIndex = uint32;

class Renderable : public Component
{
    friend class Renderer;

public:
    Renderable(Entity* owner);
    Renderable(Entity* owner, RenderLayerIndex layerIndex);
    ~Renderable();

    MaterialInstance& GetMaterial();
    const MaterialInstance& GetMaterial() const;
    void SetMaterialInstance(const MaterialInstance& instance);

    std::shared_ptr<GeometryResourceWrapper> GetGeometry();
    void SetGeometry(std::shared_ptr<GeometryResourceWrapper> geom);

    AABB& GetAABB();
    void SetAABB(const AABB& aabb);

    Vector2& GetSize();
    void SetSize(const Vector2& size);

    void SetRenderLayerIndex(RenderLayerIndex layerIndex);
    RenderLayerIndex GetRenderLayerIndex() const;

    bool IsValid() const;

    void Hide();
    void Show();

protected:
    bool m_visible;
    RenderLayerIndex m_layerIndex;
    Vector2 m_size;
    AABB m_aabb;
    std::shared_ptr<GeometryResourceWrapper> m_geometry;
    MaterialInstance m_material;
};
}  // namespace red
