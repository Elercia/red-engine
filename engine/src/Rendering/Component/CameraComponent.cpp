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

CameraComponent::CameraComponent(Entity* entity) : Component(entity), m_attachedWindow(nullptr)
{
    UpdateMatricesIfNeeded();
}

CameraComponent::CameraComponent(Entity* entity, WindowComponent* attachedWindow)
    : Component(entity), m_attachedWindow(attachedWindow->GetOwner())
{
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

Vector4i CameraComponent::ViewportRect() const
{
    if (m_attachedWindow == nullptr)
        return {0, 0, 0, 0};

    WindowInfo windowInfo = m_attachedWindow->GetComponent<WindowComponent>()->GetWindowInfo();

    Vector4i viewport((int) (m_viewport.x * (float) windowInfo.width), (int) (m_viewport.y * (float) windowInfo.height),
                      (int) (m_viewport.width * (float) windowInfo.width),
                      (int) (m_viewport.height * (float) windowInfo.height));

    return viewport;
}

const Vector4& CameraComponent::Viewport() const
{
    return m_viewport;
}

void CameraComponent::SetViewport(const Vector4& viewport)
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

const WindowComponent* CameraComponent::GetAttachedWindow() const
{
    return m_attachedWindow->GetComponent<WindowComponent>();
}

void CameraComponent::SetAttachedWindow(const WindowComponent* window)
{
    m_attachedWindow = window->GetOwner();

    UpdateMatricesIfNeeded();
}

void CameraComponent::UpdateMatricesIfNeeded()
{
    if (m_attachedWindow == nullptr)
        return;
    auto windowInfo = m_attachedWindow->GetComponent<WindowComponent>()->GetWindowInfo();
    auto* transform = GetOwner()->GetComponent<Transform>();

    const Vector2i windowSize(windowInfo.width, windowInfo.height);
    auto& worldPosition = transform->GetPosition();
    auto pos = Vector3(worldPosition, transform->GetDepth());

    m_projectionMatrix = Math::Ortho(
        m_viewport.x * (float) windowSize.width, m_viewport.width * (float) windowSize.width,
        m_viewport.y * (float) windowSize.height, m_viewport.height * (float) windowSize.height, m_zNear, m_zFar);
    m_viewMatrix = transform->GetWorldMatrix();

    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

}  // namespace red
