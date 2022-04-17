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

CameraComponent::CameraComponent(Entity* entity)
    : Component(entity), m_attachedWindow(nullptr), m_frameBuffer(true, 1), m_viewport(0.f, 0.f, 1.f, 1.f), m_size(10)
{
    UpdateState();
}

CameraComponent::CameraComponent(Entity* entity, WindowComponent* attachedWindow, const Vector4& viewport, int size)
    : Component(entity), m_attachedWindow(attachedWindow->GetOwner()), m_frameBuffer(true, 1), m_viewport(viewport), m_size(size)
{
    UpdateState();
}

CameraComponent::~CameraComponent()
{
    m_frameBuffer.Finalize();
}

bool CameraComponent::IsVisibleFrom(const AABB& /*aabb*/) const
{
    // TODO implement
    return true;
}

Vector4i CameraComponent::GetWindowRect() const
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

    UpdateState();
}

void CameraComponent::UpdateState()
{
    if (m_attachedWindow == nullptr)
        return;

    auto windowInfo = m_attachedWindow->GetComponent<WindowComponent>()->GetWindowInfo();

    float aspectRatio = (float) windowInfo.width / (float) windowInfo.height;

    auto* transform = GetOwner()->GetComponent<Transform>();

    m_projectionMatrix = Math::Ortho(0.f, (float) m_size * aspectRatio, 0.f, (float) m_size, m_zNear, m_zFar);
    m_viewMatrix = transform->GetWorldMatrix();

    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;

    // m_frameBuffer.Init(Vector2i(viewportRect.width, viewportRect.height));
}

}  // namespace red
