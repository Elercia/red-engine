#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Math/AABB.hpp"
#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Rendering/Color.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/FrameBuffer.hpp"
#include "RedEngine/Rendering/GPUBuffer.hpp"
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
    MaterialInstance materialInstance;
    AABB aabb;
    Vector2 size;
};

struct PerCameraData
{
    Matrix44 viewProj;
};

struct PerInstanceData
{
    Matrix44 world;
    Vector2 size;
};

class Renderer
{
private:
    struct RenderPassDesc
    {
        bool alphaBlending = false;
        const char* name = "Unknown";
        RenderEntityType renderType = RenderEntityType::Opaque;
    };

public:
    Renderer();
    ~Renderer();

    void BeginRenderFrame();
    void EndRenderFrame();

    // Push the renderable to the corresponding render queue
    void Draw(const Renderable* renderable, const Transform* transform);

    void DrawDebugLine(const Vector2& first, const Vector2& second, const Color& color = ColorConstant::RED);

    void DrawDebugLines(const Array<Vector2>& points, const Color& color = ColorConstant::RED, bool isFilled = false);

    void DrawDebugCircle(const Vector2& center, float radius, const Color& color = ColorConstant::RED);

    void DrawDebugPoint(const Vector2& coord, const Color& color = ColorConstant::RED);

    // Draw passes
    void BeginCameraRendering(CameraComponent* camera);
    void EndCameraRendering(CameraComponent* camera);

    void RenderOpaque(CameraComponent* camera);
    void RenderTransparency(CameraComponent* camera);
    void RenderDebug(CameraComponent* camera);
    void RenderGlobalDebug();

    void RenderPass(CameraComponent* camera, const RenderPassDesc& desc);

    // Rendering resource management
    void InitRenderer(WindowComponent* window);
    void Finalise();

    void ReCreateWindow(WindowComponent* window);

private:
    Array<RenderingData>& GetVisibleRenderDatasForType(RenderEntityType type, CameraComponent* camera,
                                                       uint32& renderDataCount);

    void UseMaterial(const MaterialInstance& mat);
    void UseGeometry(const Geometry* geom);

    void FillCameraBuffer(const CameraComponent& camera);
    void FillEntityBuffer(const RenderingData& data);

private:
    OpenGlContext m_glContext;
    WindowComponent* m_window;

    // Render entities push for this frame, these will be then culled and rendered
    Array<RenderingData> m_renderingData[(uint8)RenderEntityType::Count];

    GPUBuffer m_perInstanceData;
    GPUBuffer m_perCameraData;
};

}  // namespace red
