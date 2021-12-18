#pragma once

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Rendering/Color.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"

#include <array>

namespace red
{
class Transform;

constexpr std::size_t MAX_CAMERA_COUNT = 10;

RED_COMPONENT_BASIC_FUNCTIONS_DECLARATION(CameraComponent)

class CameraComponent : public Component
{
    friend class Renderer;
    friend class RenderingSystem;

public:
    RED_START_COMPONENT_REGISTER_INHERITHED(CameraComponent, Component)
    RED_END_COMPONENT_REGISTER()

    CameraComponent(Entity* entity);
    CameraComponent(Entity* entity, const Vector2& center);
    ~CameraComponent() override = default;

    /// View ports points
    [[nodiscard]] Vector2 ViewportToWorldPoint(const Vector2& point) const;
    [[nodiscard]] Vector2 WorldToViewportPoint(const Vector2& point) const;

    void CenterOn(const Vector2& point);
    void Follow(Vector2* followPosition);

    // TODO change this to add dimensions like AABB
    [[nodiscard]] bool IsVisibleFrom(const Transform* transform);

    /// Accessors and Setters
    [[nodiscard]] const Vector2& Position() const;

    [[nodiscard]] const Vector4i& Viewport() const;
    void SetViewport(const Vector4i& viewport);

    [[nodiscard]] float AspectRatio() const;

    [[nodiscard]] int Depth() const;
    void SetDepth(int depth);

    [[nodiscard]] const Texture2D* GetRenderedTexture() const;

    [[nodiscard]] const Color& BackgroundColor() const;
    void SetBackgroundColor(const Color& color);

private:
    Texture2D* m_renderedTexture;

    /// The camera viewport (position in the window and size)
    Vector4i m_viewport;

    Vector2 m_cameraWorldPosition;

    /// Depth of the camera (defaulted to 0)
    /// Higher depth camera are rendered after (to be on top of another)
    int m_depth{0};

    /// Background color (color to clear the screen before rendering)
    Color m_backgroundColor{ColorConstant::BLACK};

    // TODO camera render texture
};
}  // namespace red
