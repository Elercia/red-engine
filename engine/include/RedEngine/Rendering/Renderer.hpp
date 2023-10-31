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
class Text;

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
    Matrix44 viewProj;
};

struct PerInstanceData
{
    Matrix33 world;
    Vector2 size;
    float renderLayer;
};

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void BeginRenderFrame();
    void EndRenderFrame(); // Flip

    // Push the renderable to the corresponding render queue
    void Draw(Text* text, const Transform* transform); // Will compute the required data for text to be rendered
    void Draw(const Renderable* renderable, const Transform* transform);

    // Flush commands
    void BeginCameraRendering(CameraComponent* camera);
    void EndCameraRendering(CameraComponent* camera);

    void RenderDebug(CameraComponent* camera, DebugComponent* debug);
    void RenderFullScreenDebugUI();

    void RenderSprites(CameraComponent* camera);

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

    void CreateText(Text* text);

private:
    OpenGlContext m_glContext;
    WindowComponent* m_window;

    // Pushed sprites data
    Array<RenderingData> m_renderingData;

    // Tmp data used per camera
    Array<RenderingData, DoubleLinearArrayAllocator> m_cameraRenderingData;

    // Rendering data sent to GPU
    GPUBuffer m_perInstanceData;
    GPUBuffer m_perCameraData;

    uint32 m_lineVertexColorVBO;
    uint32 m_lineVAO;

    std::shared_ptr<Material> m_textMaterial;
};

}  // namespace red
