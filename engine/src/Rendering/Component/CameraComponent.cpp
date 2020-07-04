
#include <RedEngine/Rendering/Component/CameraComponent.hpp>
#include <RedEngine/Math/Math.hpp>
#include <RedEngine/Core/Debug/Logger/Logger.hpp>
#include <RedEngine/Rendering/Window.hpp>

namespace red
{
CameraComponent::CameraComponent(Entity* entity, const Vector2& center)
    : Component(entity), m_renderedTexture(nullptr)
{
    auto info = Window::GetWindow().GetWindowInfo();
    m_viewport = {0, 0, static_cast<float>(info.width), static_cast<float>(info.height)};

    m_cameraWorldPosition =
        Vector2(center.x - m_viewport.width / 2.F, center.y - m_viewport.height / 2.F);
}

Vector2 red::CameraComponent::ScreenToViewportPoint(const Vector2& point) const
{
    if (!Math::Between(point.x, m_viewport.x, m_viewport.x + m_viewport.width) ||
        !Math::Between(point.y, m_viewport.y, m_viewport.y + m_viewport.height))
    {
        RED_LOG_WARNING("Camera ScreenToViewportPoint point is out of viewport");
        return {-1.F, -1.F};
    }

    Vector2 rt;

    rt.x = point.x - m_viewport.x;
    rt.y = point.y - m_viewport.y;

    return rt;
}

Vector2 CameraComponent::ViewportToScreenPoint(const Vector2& point) const
{
    Vector2 rt;

    rt.x = point.x + m_viewport.x;
    rt.y = point.y + m_viewport.y;

    return rt;
}

Vector2 CameraComponent::ViewportToWorldPoint(const Vector2& point) const
{
    Vector2 rt;

    rt.x = point.x + m_cameraWorldPosition.x;
    rt.y = point.y + m_cameraWorldPosition.y;

    return rt;
}

Vector2 CameraComponent::ScreenToWorldPoint(const Vector2& point) const
{
    Vector2 rt;

    rt.x = point.x - m_viewport.x + m_cameraWorldPosition.x;
    rt.y = point.y - m_viewport.y + m_cameraWorldPosition.y;

    return rt;
}

Vector2 CameraComponent::WorldToScreenPoint(const Vector2& point) const
{
    Vector2 rt;

    rt.x = point.x + m_viewport.x - m_cameraWorldPosition.x;
    rt.y = point.y + m_viewport.y - m_cameraWorldPosition.y;

    return rt;
}
Vector2 CameraComponent::WorldToViewportPoint(const Vector2& point) const
{
    Vector2 rt;

    rt.x = point.x + m_viewport.x - m_cameraWorldPosition.x;
    rt.y = point.y + m_viewport.y - m_cameraWorldPosition.y;

    return rt;
}

void CameraComponent::CenterOn(const Vector2& point)
{
    m_cameraWorldPosition.x = point.x - m_viewport.width / 2.F;
    m_cameraWorldPosition.y = point.y - m_viewport.height / 2.F;
}

void CameraComponent::Follow(Vector2* followPosition)
{
    // TODO
}

bool CameraComponent::IsVisibleFrom(const Transform* transform) { return true; }

const Vector2& CameraComponent::Position() const { return m_cameraWorldPosition; }

const Vector4& CameraComponent::Viewport() const { return m_viewport; }

void CameraComponent::SetViewport(const Vector4& viewport) { m_viewport = viewport; }

float CameraComponent::AspectRatio() const { return m_viewport.z / m_viewport.w; }

int CameraComponent::Depth() const { return m_depth; }

void CameraComponent::SetDepth(int depth) { m_depth = depth; }

std::shared_ptr<const Texture2D> CameraComponent::GetRenderedTexture() const
{
    return m_renderedTexture;
}

const Color& CameraComponent::BackgroundColor() const { return m_backgroundColor; }

void CameraComponent::SetBackgroundColor(const Color& color) { m_backgroundColor = color; }

}  // namespace red
