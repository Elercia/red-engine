
#include "RedEngine/Rendering/Component/CameraComponent.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Math/Math.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(CameraComponent)

CameraComponent::CameraComponent(Entity* entity) : CameraComponent(entity, {0.f,0.f})
{
}

CameraComponent::CameraComponent(Entity* entity, const Vector2& center) : Component(entity), m_renderedTexture(nullptr)
{
    auto* window = entity->GetWorld()->GetWorldComponent<WindowComponent>();

    if (window == nullptr)
    {
        RED_LOG_ERROR("Camera component created without a window");
        return;
    }

    auto info = window->GetWindowInfo();

    m_viewport = {0, 0, info.width, info.height};

    m_cameraWorldPosition =
        Vector2(center.x - (float) m_viewport.width / 2.F, center.y - (float) m_viewport.height / 2.F);
}

Vector2 CameraComponent::ViewportToWorldPoint(const Vector2& point) const
{
    Vector2 rt;

    rt.x = point.x + m_cameraWorldPosition.x;
    rt.y = point.y + m_cameraWorldPosition.y;

    return rt;
}

Vector2 CameraComponent::WorldToViewportPoint(const Vector2& point) const
{
    Vector2 rt;

    rt.x = point.x + (float) m_viewport.x - m_cameraWorldPosition.x;
    rt.y = point.y + (float) m_viewport.y - m_cameraWorldPosition.y;

    return rt;
}

void CameraComponent::CenterOn(const Vector2& point)
{
    m_cameraWorldPosition.x = point.x - (float) m_viewport.width / 2.F;
    m_cameraWorldPosition.y = point.y - (float) m_viewport.height / 2.F;
}

void CameraComponent::Follow(Vector2* /*followPosition*/)
{
    // TODO
}

bool CameraComponent::IsVisibleFrom(const Transform* /*transform*/)
{
    return true;
}

const Vector2& CameraComponent::Position() const
{
    return m_cameraWorldPosition;
}

const Vector4i& CameraComponent::Viewport() const
{
    return m_viewport;
}

void CameraComponent::SetViewport(const Vector4i& viewport)
{
    m_viewport = viewport;
}

float CameraComponent::AspectRatio() const
{
    return (float) m_viewport.width / (float) m_viewport.height;
}

int CameraComponent::Depth() const
{
    return m_depth;
}

void CameraComponent::SetDepth(int depth)
{
    m_depth = depth;
}

const Texture2D* CameraComponent::GetRenderedTexture() const
{
    return m_renderedTexture;
}

const Color& CameraComponent::BackgroundColor() const
{
    return m_backgroundColor;
}

void CameraComponent::SetBackgroundColor(const Color& color)
{
    m_backgroundColor = color;
}

}  // namespace red
