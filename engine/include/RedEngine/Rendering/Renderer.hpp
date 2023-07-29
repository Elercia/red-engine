#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Memory/LinearAllocator.hpp"
#include "RedEngine/Math/AABB.hpp"
#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Rendering/Color.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/Renderable.hpp"
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

    bool hasBeenRendered;
};

struct PerCameraData
{
    Matrix44 viewProj;
};

struct PerInstanceData
{
    Matrix33 world;
    Vector2 size;
    float renderLayer;
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
    };

public:
    Renderer();
    ~Renderer();

    void BeginRenderFrame();
    void EndRenderFrame();

    // Push the renderable to the corresponding render queue
    void Draw(const Renderable* renderable, const Transform* transform);

    // Draw passes
    void BeginCameraRendering(CameraComponent* camera);
    void EndCameraRendering(CameraComponent* camera);

    void RenderOpaqueQueue(CameraComponent* camera);
    void RenderTransparencyQueue(CameraComponent* camera);

    void RenderDebug(CameraComponent* camera, DebugComponent* debug);
    void RenderDebugUI();

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

    // Tmp data used per camera
    Array<RenderingData, DoubleLinearArrayAllocator> m_culledAndSortedRenderingData;
    ArrayView<RenderingData> m_renderingDataPerQueue[(int) RenderEntityType::Count];

    // Rendering data sent to GPU
    GPUBuffer m_perInstanceData;
    GPUBuffer m_perCameraData;

    uint32 m_lineVertexColorVBO;
    uint32 m_lineVAO;
};

}  // namespace red
