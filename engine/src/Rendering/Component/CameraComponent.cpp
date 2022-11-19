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
    : Component(entity)
    , m_attachedWindow(nullptr)
    , m_frameBuffer(true, 1)
    , m_screenViewport(0.f, 0.f, 1.f, 1.f)
    , m_size(0.f, 0.f)
{
    UpdateState();
}

CameraComponent::CameraComponent(Entity* entity, WindowComponent* attachedWindow, const Vector4& sceenViewport,
                                 const Vector2& size)
    : Component(entity)
    , m_attachedWindow(attachedWindow->GetOwner())
    , m_frameBuffer(true, 1)
    , m_screenViewport(sceenViewport)
    , m_size(size)
{
    UpdateState();
}

CameraComponent::~CameraComponent()
{
    m_frameBuffer.Finalize();
}

bool CameraComponent::IsVisibleFrom(const AABB& aabb) const
{
    AABB thisAabb(GetOwner()->GetComponent<Transform>()->GetPosition(),
                  {m_size.x, m_size.y});  // TODO put it in camera cached state

    return thisAabb.Intersect(aabb);
}

Vector4i CameraComponent::GetWindowRect() const
{
    if (m_attachedWindow == nullptr)
        return {0, 0, 0, 0};

    WindowInfo windowInfo = m_attachedWindow->GetComponent<WindowComponent>()->GetWindowInfo();

    Vector4i viewport((int) (m_screenViewport.x * (float) windowInfo.width),
                      (int) (m_screenViewport.y * (float) windowInfo.height),
                      (int) (m_screenViewport.width * (float) windowInfo.width),
                      (int) (m_screenViewport.height * (float) windowInfo.height));

    return viewport;
}

const Vector4& CameraComponent::Viewport() const
{
    return m_screenViewport;
}

void CameraComponent::SetViewport(const Vector4& viewport)
{
    m_screenViewport = viewport;
}

float CameraComponent::AspectRatio() const
{
    return (float) m_screenViewport.width / (float) m_screenViewport.height;
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

const Matrix33& CameraComponent::GetView() const
{
    return m_viewMatrix;
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

    auto* transform = GetOwner()->GetComponent<Transform>();
    m_viewMatrix = transform->GetWorldMatrix();

    // m_frameBuffer.Init(Vector2i(viewportRect.width, viewportRect.height));
}

}  // namespace red
