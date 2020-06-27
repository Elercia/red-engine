#pragma once

#include <array>

#include <RedEngine/Core/Components/Component.hpp>
#include <RedEngine/Rendering/Texture2D.hpp>
#include <RedEngine/Math/Vector.hpp>
#include <RedEngine/Rendering/Color.hpp>
#include <RedEngine/Math/Matrix.hpp>

namespace red
{
class Transform;

constexpr std::size_t MAX_CAMERA_COUNT = 10;

class CameraComponent : public Component
{
    friend class RenderingEngine;
    friend class RenderingSystem;

public:
    CameraComponent(Entity* entity, const Vector2& center);
    ~CameraComponent() override = default;

    /// View ports points
    [[nodiscard]] Vector2 ScreenToViewportPoint(const Vector2& point) const;
    [[nodiscard]] Vector2 ViewportToScreenPoint(const Vector2& point) const;
    [[nodiscard]] Vector2 ViewportToWorldPoint(const Vector2& point) const;
    [[nodiscard]] Vector2 ScreenToWorldPoint(const Vector2& point) const;
    [[nodiscard]] Vector2 WorldToScreenPoint(const Vector2& point) const;
    [[nodiscard]] Vector2 WorldToViewportPoint(const Vector2& point) const;

    void CenterOn(const Vector2& point);
    void Follow(Vector2* followPosition);

    // TODO change this to add dimensions like AABB
    [[nodiscard]] bool IsVisibleFrom(const Transform* transform);

    /// Accessors and Setters
    [[nodiscard]] const Vector2& Position() const;

    [[nodiscard]] const Vector4& Viewport() const;
    void SetViewport(const Vector4& viewport);

    [[nodiscard]] float AspectRatio() const;

    [[nodiscard]] int Depth() const;
    void SetDepth(int depth);

    [[nodiscard]] std::shared_ptr<const Texture2D> GetRenderedTexture() const;

    [[nodiscard]] const Color& BackgroundColor() const;
    void SetBackgroundColor(const Color& color);

private:
    std::shared_ptr<Texture2D> m_renderedTexture;

    /// The camera viewport (position in the window and size)
    Vector4 m_viewport;

    Vector2 m_cameraWorldPosition;

    /// Depth of the camera (defaulted to 0)
    /// Higher depth camera are rendered after (to be on top of another)
    int m_depth{0};

    /// Background color (color to clear the screen before rendering)
    Color m_backgroundColor{ColorConstant::BLACK};
};
}  // namespace red
