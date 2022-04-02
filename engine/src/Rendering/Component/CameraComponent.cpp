#include "RedEngine/Rendering/Component/CameraComponent.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Math/Math.hpp"
#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Math/MatrixFunctions.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Rendering/Component/Renderable.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(CameraComponent)

CameraComponent::CameraComponent(Entity* entity) : Component(entity)
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

bool CameraComponent::IsVisibleFrom(const AABB& /*aabb*/) const
{
    // TODO implement
    return true;
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

const Color& CameraComponent::GetClearColor() const
{
    return m_cleanColor;
}

void CameraComponent::SetClearColor(const Color& color)
{
    m_cleanColor = color;
}

const Matrix44& CameraComponent::GetViewProjection() const
{
    return m_viewProjectionMatrix;
}

void CameraComponent::UpdateMatricesIfNeeded()
{
    auto* transform = GetOwner()->GetComponent<Transform>();
    auto& worldPosition = transform->GetPosition();
    auto pos = Vector3(worldPosition, transform->GetDepth());

    m_projectionMatrix = Math::Ortho(0.f, (float) m_viewport.width, 0.f, (float) m_viewport.height, m_zNear, m_zFar);
    m_viewMatrix = transform->GetWorldMatrix();

    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

}  // namespace red
