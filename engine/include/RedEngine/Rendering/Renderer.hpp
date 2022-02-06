#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Math/AABB.hpp"
#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Rendering/Color.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Resource/Geometry.hpp"
#include "RedEngine/Rendering/Resource/Material.hpp"

#include <memory>
#include <string>

namespace red
{
class WindowComponent;
class Renderable;
class CameraComponent;

using OpenGlContext = void*;

struct RenderingData
{
    Matrix44 worldMatrix;
    Geometry* geometry;
    std::shared_ptr<Material> material;
    AABB aabb;
    CameraComponent* camera;
};

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void BeginRenderFrame();
    void EndRenderFrame();

    // Push the renderable to the corresponding render queue
    void Render(const Renderable* renderable, const Transform* transform);

    // Draw passes
    void BeginCameraRendering(CameraComponent* camera);
    void EndCameraRendering(CameraComponent* camera);

    void RenderOpaque(CameraComponent* camera);
    void RenderTransparency(CameraComponent* camera);
    void RenderLights(CameraComponent* camera);

    void DrawLine(CameraComponent* camera, const Vector2& first, const Vector2& second,
                  const Color& color = ColorConstant::RED);

    void DrawLines(CameraComponent* camera, const Array<Vector2>& points, const Color& color = ColorConstant::RED,
                   bool isFilled = false);

    void DrawCircle(CameraComponent* camera, const Vector2& center, float radius,
                    const Color& color = ColorConstant::RED);

    void DrawPoint(CameraComponent* camera, const Vector2& coord, const Color& color = ColorConstant::RED);

    void InitRenderer(WindowComponent* window);
    void Finalise();

private:
    Array<RenderingData>& GetVisibleRenderDatasForType(RenderEntityType type, CameraComponent* camera,
                                                       int& renderDataCount);

    void UseMaterial(const std::shared_ptr<Material>& mat);
    void UseGeometry(const Geometry* geom);

private:
    OpenGlContext m_glContext;
    WindowComponent* m_window;

    // Render entities push for this frame, these will be then culled and rendered
    Array<RenderingData> m_renderingData[RenderEntityType::Count];
};

}  // namespace red
