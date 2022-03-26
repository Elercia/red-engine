#pragma once

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Math/AABB.hpp"
#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Rendering/Color.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"

#include <array>

namespace red
{
class Transform;
class Renderable;

RED_COMPONENT_BASIC_FUNCTIONS_DECLARATION(CameraComponent)

class CameraComponent : public Component
{
    friend class Renderer;
    friend class RenderingSystem;

public:
    RED_START_COMPONENT_REGISTER_INHERITHED(CameraComponent, Component)
    RED_MEMBER("viewport", m_viewport, "The viewport (postion on window & size) of the camera", 0);
    RED_MEMBER("depth", m_depth, "The depth of the camera", 0);
    RED_MEMBER("zNear", m_zNear, "The projection zNear", 0);
    RED_MEMBER("zFar", m_zFar, "The projection zFar", 0);
    RED_END_COMPONENT_REGISTER()

    CameraComponent(Entity* entity);
    virtual ~CameraComponent() = default;

    /// View ports points
    [[nodiscard]] Vector2 ViewportToWorldPoint(const Vector2& point) const;
    [[nodiscard]] Vector2 WorldToViewportPoint(const Vector2& point) const;

    // Return true if the given AABB is visible from the given camera
    [[nodiscard]] bool IsVisibleFrom(const AABB& aabb) const;

    [[nodiscard]] const Vector4i& Viewport() const;
    void SetViewport(const Vector4i& viewport);

    [[nodiscard]] float AspectRatio() const;

    [[nodiscard]] float Depth() const;
    void SetDepth(float depth);

    [[nodiscard]] const Color& GetClearColor() const;
    void SetClearColor(const Color& color);

    void UpdateMatricesIfNeeded();

    const Matrix44& GetViewProjection() const;

private:
    /// The camera viewport (position in the window and size)
    Vector4i m_viewport;

    /// Depth of the camera (defaulted to 0)
    /// Higher depth camera are rendered after (to be on top of another)
    float m_depth{0};

    /// Background color (color to clear the screen before rendering)
    Color m_cleanColor{ColorConstant::BLACK};

    float m_zNear{0.1f};
    float m_zFar{1000.0f};

    Matrix44 m_viewMatrix;
    Matrix44 m_projectionMatrix;
    Matrix44 m_viewProjectionMatrix;
};
}  // namespace red
