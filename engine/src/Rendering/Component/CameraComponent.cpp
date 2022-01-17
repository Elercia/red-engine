#include "RedEngine/Rendering/Component/CameraComponent.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Math/Math.hpp"
#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Math/MatrixFunctions.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(CameraComponent)

CameraComponent::CameraComponent(Entity* entity) : CameraComponent(entity, {0.f, 0.f})
{
}

CameraComponent::CameraComponent(Entity* entity, const Vector2& center) : Component(entity)
{
    auto* window = entity->GetWorld()->GetWorldComponent<WindowComponent>();

    if (window == nullptr)
    {
        RED_LOG_ERROR("Camera component created without a window");
        m_viewport = {0, 0, 1, 1};
    }
    else
    {
        auto info = window->GetWindowInfo();
        m_viewport = {0, 0, info.width, info.height};
    }

    m_center = center;

    UpdateMatricesIfNeeded();
}

Vector2 CameraComponent::ViewportToWorldPoint(const Vector2& /*point*/) const
{
    return {0.f, 0.f};
}

Vector2 CameraComponent::WorldToViewportPoint(const Vector2& /*point*/) const
{
    return {0.f, 0.f};
}

bool CameraComponent::IsVisibleFrom(const Transform* /*transform*/)
{
    return true;
}

void CameraComponent::CenterOn(const Vector2& point)
{
    m_center = point;
    m_bDirtyMatrix = true;
}

const Vector2& CameraComponent::Center() const
{
    return m_center;
}

const Vector4i& CameraComponent::Viewport() const
{
    return m_viewport;
}

void CameraComponent::SetViewport(const Vector4i& viewport)
{
    m_viewport = viewport;
    m_bDirtyMatrix = true;
}

float CameraComponent::AspectRatio() const
{
    return (float) m_viewport.width / (float) m_viewport.height;
}

float CameraComponent::Depth() const
{
    return m_depth;
}

void CameraComponent::SetDepth(float depth)
{
    m_depth = depth;
    m_bDirtyMatrix = true;
}

const Color& CameraComponent::GetClearColor() const
{
    return m_cleanColor;
}

void CameraComponent::SetClearColor(const Color& color)
{
    m_cleanColor = color;
}

void CameraComponent::UpdateMatricesIfNeeded()
{
    if (m_bDirtyMatrix)
    {
        m_bDirtyMatrix = false;

        m_projectionMatrix = Math::Ortho(0.0f, (float) m_viewport.x, 0.0f, (float) m_viewport.y, m_zNear, m_zFar);

        const Vector2 midOffset = Vector2((float)m_viewport.x * 0.5f, (float)m_viewport.y * 0.5f);
        const Vector3 position =
            Vector3(m_center.x - ((float)m_viewport.x * 0.5f), m_center.y - ((float)m_viewport.y * 0.5f), m_depth);

        m_viewMatrix = Matrix44::Identity();
        m_viewMatrix = Math::Translate(m_viewMatrix, position);
        m_viewMatrix = Math::Translate(m_viewMatrix, Vector3(midOffset, 0.0));
        m_viewMatrix = Math::Rotate(m_viewMatrix, Vector3(0.0f, 0.0f, Math::ToRadians(m_rotationAngle)));
        m_viewMatrix = Math::Translate(m_viewMatrix, Vector3(-midOffset, 0.0));

        m_viewProjectionMatrix = m_viewMatrix * m_projectionMatrix;
    }
}

}  // namespace red
