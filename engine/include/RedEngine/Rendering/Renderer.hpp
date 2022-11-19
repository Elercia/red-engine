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
    RenderLayerIndex renderLayerIndex;
    RenderEntityType type;

    Matrix33 worldMatrix;
    Geometry* geometry;
    MaterialInstance materialInstance;
    AABB aabb;
    Vector2 size;
};

struct PerCameraData
{
    Matrix33 worldToView;
    Matrix33 viewToClip;
};

struct PerInstanceData
{
    Matrix33 world;
    Vector2 size;
};

using RenderDataArrayPerType = std::array<Array<RenderingData>, (uint8) RenderEntityType::Count>;
using RenderDataPerLayer = std::array<RenderDataArrayPerType, 32>;

class Renderer
{
private:
    struct RenderPassDesc
    {
        bool alphaBlending = false;
        const char* name = "Unknown";
        RenderEntityType renderType = RenderEntityType::Opaque;
        RenderLayerIndex layerIndex = 0;
    };

public:
    Renderer();
    ~Renderer();

    void BeginRenderFrame();
    void EndRenderFrame();

    // Push the renderable to the corresponding render queue
    void Draw(const Renderable* renderable, const Transform* transform);

    void DrawDebugLine(const Vector2& first, const Vector2& second, const Color& color = ColorConstant::RED);

    void DrawDebugCircle(const Vector2& center, float radius, const Color& color = ColorConstant::RED);

    void DrawDebugPoint(const Vector2& coord, const Color& color = ColorConstant::YELLOW);

    // Draw passes
    void BeginCameraRendering(CameraComponent* camera);
    void EndCameraRendering(CameraComponent* camera);

    void RenderLayerOpaque(RenderLayerIndex layerIndex, CameraComponent* camera);
    void RenderLayerTransparency(RenderLayerIndex layerIndex, CameraComponent* camera);

    void RenderDebug(CameraComponent* camera);
    void RenderGlobalDebug();

    void RenderPass(CameraComponent* camera, const RenderPassDesc& desc);

    // Rendering resource management
    void InitRenderer(WindowComponent* window);
    void Finalise();

    void ReCreateWindow(WindowComponent* window);

private:
    void CullRenderDataForCamera(CameraComponent* camera);

    void UseMaterial(const MaterialInstance& mat);
    void UseGeometry(const Geometry* geom);

    void FillCameraBuffer(const CameraComponent& camera);
    void FillEntityBuffer(const RenderingData& data);

private:
    OpenGlContext m_glContext;
    WindowComponent* m_window;

    // Complex drawed sprites
    Array<RenderingData> m_renderingData;

    // Debug data (rendered rebug primitives)
    Array<Vector2> m_debugLines;
    Array<Color> m_debugLineColors;

    // Tmp data used per camera
    Array<RenderingData, DoubleLinearArrayAllocator> m_culledAndSortedRenderingData;
    uint32 m_maxRenderDataLastFrame;
    ArrayView<RenderingData> m_renderingDataPerLayer[32];

    // Rendering data sent to GPU
    GPUBuffer m_perInstanceData;
    GPUBuffer m_perCameraData;
};

}  // namespace red
