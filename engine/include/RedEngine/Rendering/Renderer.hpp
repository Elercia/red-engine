#pragma once

#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"

#include <memory>
#include <string>
#include <vector>

#include "Color.hpp"

namespace red
{
class WindowComponent;
class Renderable;
class CameraComponent;

using OpenGlContext = void*;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void BeginCameraRendering(CameraComponent* cameraComponent);
    void EndCameraRendering();

    void BeginRenderFrame();
    void EndRenderFrame();

    void Render(CameraComponent* camera, Renderable* renderable, const Transform& transform);

    void DrawLine(CameraComponent* camera, const Vector2& first, const Vector2& second,
                  const Color& color = ColorConstant::RED);

    void DrawLines(CameraComponent* camera, const std::vector<Vector2>& points, const Color& color = ColorConstant::RED,
                   bool isFilled = false);

    void DrawCircle(CameraComponent* camera, const Vector2& center, float radius,
                    const Color& color = ColorConstant::RED);

    void DrawPoint(CameraComponent* camera, const Vector2& coord, const Color& color = ColorConstant::RED);

    void InitRenderer(WindowComponent* window);

private:
    OpenGlContext m_glContext;
    WindowComponent* m_window;
};

}  // namespace red
