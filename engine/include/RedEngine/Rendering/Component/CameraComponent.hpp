#pragma once

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Math/AABB.hpp"
#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Rendering/Color.hpp"
#include "RedEngine/Rendering/FrameBuffer.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"

#include <array>

namespace red
{
class Transform;
class Renderable;
class Entity;
class WindowComponent;

RED_COMPONENT_BASIC_FUNCTIONS_DECLARATION(CameraComponent)

class CameraComponent : public Component
{
    friend class Renderer;
    friend class RenderingSystem;

public:
    RED_START_COMPONENT_REGISTER_INHERITHED(CameraComponent, Component)
    RED_MEMBER("viewport", m_screenViewport, "The viewport (postion on window & size) of the camera", 0);
    RED_MEMBER("size", m_size, "The size of this camera in the world", 0);
    RED_MEMBER("depth", m_depth, "The depth of the camera", 0);
    RED_MEMBER("zNear", m_zNear, "The projection zNear", 0);
    RED_MEMBER("zFar", m_zFar, "The projection zFar", 0);
    RED_END_COMPONENT_REGISTER()

    CameraComponent(Entity* entity);
    CameraComponent(Entity* entity, WindowComponent* attachedWindow, const Vector4& viewport, const Vector2& size);
    virtual ~CameraComponent();

    // Return true if the given AABB is visible from the given camera
    [[nodiscard]] bool IsVisibleFrom(const AABB& aabb) const;

    [[nodiscard]] Vector4i GetWindowRect() const;
    [[nodiscard]] const Vector4& Viewport() const;
    void SetViewport(const Vector4& viewport);

    [[nodiscard]] const WindowComponent* GetAttachedWindow() const;
    void SetAttachedWindow(const WindowComponent* window);

    [[nodiscard]] float AspectRatio() const;

    [[nodiscard]] int Depth() const;
    void SetDepth(int depth);

    [[nodiscard]] const Color& GetClearColor() const;
    void SetClearColor(const Color& color);

    void UpdateState();

    const Matrix44& GetViewProj() const;

private:
    Entity* m_attachedWindow;
    FrameBuffer m_frameBuffer;

    // The camera viewport
    // This describe where the camera will be drawn on the screen
    Vector4 m_screenViewport;

    // Describe the size of the camera inside the world
    Vector2 m_size;

    /// Depth of the camera (defaulted to 0)
    /// Higher depth camera are rendered after (to be on top of another)
    int m_depth{0};

    /// Background color (color to clear the screen before rendering)
    Color m_cleanColor{ColorConstant::BLACK};

    float m_zNear{0.001f};
    float m_zFar{1000.0f};

    Matrix44 m_viewProj;
};
}  // namespace red
