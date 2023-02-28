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
template <>
void RegisterMembers<CameraComponent>(ComponentTraits& traits)
{
    traits.AddMember("Screen Viewport", &CameraComponent::m_screenViewport, "The position inside the view of the camera (0-1)", 0);
    traits.AddMember("Size", &CameraComponent::m_size, "The size of the camera inside the world", 0);
    traits.AddMember("Order", &CameraComponent::m_depth, "The order of rendering", 0);
    traits.AddMember("Clear color", &CameraComponent::m_cleanColor, "The color used to clear the buffer of this camera", 0);
}

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
    AABB thisAabb(GetOwner()->GetComponent<Transform>()->GetLocalPosition(),
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

const Matrix44& CameraComponent::GetViewProj() const
{
    return m_viewProj;
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
    auto rotRad = transform->GetLocalRotationRad();
    auto& scale = transform->GetScale();

    Matrix44 view = Math::Translate(Matrix44::Identity(), Vector3(transform->GetLocalPosition(), 0.f));
    view = Math::Rotate(view, Vector3(0.f, 0.f, rotRad));
    view = Math::Scale(view, Vector3(scale, 1.f));

    Matrix44 proj = Math::Ortho(0.0f, m_size.x, 0.f, m_size.y, -1.f, 100.0f);
    m_viewProj = proj * view;

    // m_frameBuffer.Init(Vector2i(viewportRect.width, viewportRect.height));
}

}  // namespace red
