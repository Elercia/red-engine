#include "RedEngine/Rendering/Renderer.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"
#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/Renderable.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/Resource/Material.hpp"
#include "RedEngine/Rendering/Resource/ShaderProgram.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"
#include "RedEngine/Utils/Types.hpp"

// clang-format off
#include <GL/gl3w.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
// clang-format on

#define CheckGLReturnValue(expr, ...) \
    if ((expr) != 0)                  \
    {                                 \
        RED_LOG_ERROR(__VA_ARGS__);   \
    }

namespace red
{
const int PrimitiveTypesAsGLTypes[] = {
    GL_TRIANGLES, GL_QUADS, GL_LINES, GL_POINTS, GL_LINE_LOOP, GL_LINE_STRIP, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN,
};

Renderer::Renderer()
    : m_glContext(nullptr)
    , m_window(nullptr)
    , m_perInstanceData(1, sizeof(PerInstanceData))
    , m_perCameraData(1, sizeof(PerCameraData))
{
}

Renderer::~Renderer()
{
}

void Renderer::InitRenderer(WindowComponent* window)
{
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
    {
        RED_LOG_ERROR("Error initializing SDL_Video with error {}", SDL_GetError());
        SDL_Quit();
        RED_ABORT("Cannot initialize Renderer");
    }

    // Request OpenGL 4.3 context.
    CheckGLReturnValue(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) != 0,
                       "Error setting gl context major version with error {}", SDL_GetError());
    CheckGLReturnValue(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4) != 0,
                       "Error setting gl context major version with error {}", SDL_GetError());

    // set double buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = window;
    m_window->CreateNewWindow();

    m_glContext = SDL_GL_CreateContext(window->GetSDLWindow());
    if (m_glContext == nullptr)
    {
        RED_LOG_ERROR("Failed to query openGL context from SDL");
        return;
    }

    if (gl3wInit() != 0)
    {
        RED_LOG_ERROR("Failed to query openGL context from SDL");
        return;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_perInstanceData.Init();
    m_perCameraData.Init();

    RED_LOG_INFO("Init OpenGL renderer");
}

void Renderer::ReCreateWindow(WindowComponent* /*window*/)
{
    // TODO recreate frame buffer etc
}

void Renderer::Finalise()
{
    m_perInstanceData.Finalize();
    m_perCameraData.Finalize();

    SDL_GL_DeleteContext(m_glContext);

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void Renderer::BeginRenderFrame()
{
    auto windowInfo = m_window->GetWindowInfo();
    glViewport(0, 0, windowInfo.width, windowInfo.height);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::EndRenderFrame()
{
    // Clear the current render data for the current camera
    for (Array<RenderingData>& passesDatas : m_renderingData)
    {
        passesDatas.clear();
    }

    SDL_GL_SwapWindow(m_window->GetSDLWindow());
}

void Renderer::BeginCameraRendering(CameraComponent* cameraComponent)
{
    cameraComponent->UpdateMatricesIfNeeded();
    
    // Setup the camera viewport
    glViewport(cameraComponent->m_viewport.x, cameraComponent->m_viewport.y, cameraComponent->m_viewport.width,
               cameraComponent->m_viewport.height);

    glClearColor(cameraComponent->m_cleanColor.r / 255.f, cameraComponent->m_cleanColor.g / 255.f,
                 cameraComponent->m_cleanColor.b / 255.f, cameraComponent->m_cleanColor.a / 255.f);
}

void Renderer::EndCameraRendering(CameraComponent* /*camera*/)
{
}

void Renderer::Draw(const Renderable* renderable, const Transform* transform)
{
    RenderingData data;
    data.geometry = &(renderable->m_geometry->m_geom);
    data.materialInstance = renderable->m_material;
    data.worldMatrix = transform->GetWorldMatrix();
    data.aabb = renderable->m_aabb;
    data.size = renderable->m_size;

    auto& renderDatasForCamera = m_renderingData[data.materialInstance.material->GetRenderType()];
    renderDatasForCamera.push_back(std::move(data));
}

void Renderer::DrawDebugLine(const Vector2& /*first*/, const Vector2& /*second*/, const Color& /*color*/)
{
}

void Renderer::DrawDebugLines(const Array<Vector2>& /*points*/, const Color& /*color*/ /*= ColorConstant::RED*/,
                              bool /*isFilled*/ /*= false*/)  // TODO isFilled
{
}

void Renderer::DrawDebugCircle(const Vector2& /*center*/, float /*radius*/,
                               const Color& /*color*/ /*= ColorConstant::RED*/)
{
}

void Renderer::DrawDebugPoint(const Vector2& /*coord*/, const Color& /*color*/ /*= ColorConstant::RED*/)
{
}

void Renderer::RenderOpaque(CameraComponent* camera)
{
    PROFILER_CATEGORY("RenderOpaque", Optick::Category::Rendering);

    uint64 count = 0;
    Array<RenderingData>& datas = GetVisibleRenderDatasForType(RenderEntityType::Opaque, camera, count);

    const Matrix44& projView = camera->GetViewProjection();

    glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, "Opaque");

    // Do the actual render calls to the camera render target
    for (uint64 i = 0; i < count; i++)
    {
        auto& renderData = datas[i];

        UseMaterial(renderData.materialInstance);
        UseGeometry(renderData.geometry);

        PerCameraData* perCamera = m_perCameraData.Map<PerCameraData>(MapType::WRITE);
        perCamera->viewProj = projView;
        m_perCameraData.UnMap();

        PerInstanceData* perInstance = m_perInstanceData.Map<PerInstanceData>(MapType::WRITE);
        perInstance->size = renderData.size;
        perInstance->world = renderData.worldMatrix;
        m_perInstanceData.UnMap();

        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_perCameraData.m_gpuBufferHandle);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_perInstanceData.m_gpuBufferHandle);

        auto primitiveType = renderData.geometry->GetPrimitiveType();

        glDrawElements(PrimitiveTypesAsGLTypes[(int) primitiveType], renderData.geometry->GetIndexeCount(),
                       GL_UNSIGNED_INT, nullptr);
    }

    glPopDebugGroup();
}

void Renderer::RenderTransparency(CameraComponent* /*camera*/)
{
    PROFILER_CATEGORY("RenderTransparency", Optick::Category::Rendering);
}

void Renderer::RenderDebug(CameraComponent* /*camera*/)
{
}

void Renderer::RenderGlobalDebug()
{
}

void Renderer::UseMaterial(const MaterialInstance& materialInstance)
{
    const auto& material = materialInstance.material;
    const auto& defaultBindings = material->m_defaultBindings.bindings;
    const auto& overiddenBindings = materialInstance.overiddenBindings.bindings;

    glUseProgram(material->GetShaderProgram()->m_handle);

    // Bind textures and buffers
    for (int i = 0; i < BindingIndex::Max; i++)
    {
        const BindingValue* value = nullptr;

        const auto& defaultBinding = defaultBindings[i];
        const auto& overidenBinding = overiddenBindings[i];
        if (overidenBinding.type != BindingType::None)
        {
            value = &overidenBinding;
        }
        else if (defaultBinding.type != BindingType::None)
        {
            value = &defaultBinding;
        }

        if (value != nullptr)
        {
            if (value->type == BindingType::Texture)
            {
                const auto& texture = value->texture;
                glBindTextureUnit(i, texture->m_textureHandle);
            }
            else if (value->type == BindingType::Vector4)
            {
                const auto& vector = value->floats;
                glUniform4fv(i, 1, vector);
            }
        }
    }
}

void Renderer::UseGeometry(const Geometry* geom)
{
    glEnableVertexAttribArray(0);
    glBindVertexArray(geom->m_gpuBufferHandle);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geom->m_gpuIndexBuffer);
}

Array<RenderingData>& Renderer::GetVisibleRenderDatasForType(RenderEntityType type, CameraComponent* camera,
                                                             uint64& renderDataCount)
{
    Array<RenderingData>& ret = m_renderingData[type];
    renderDataCount = ret.size();

    for (uint64 i = 0u; i < ret.size(); i++)
    {
        if (!camera->IsVisibleFrom(ret[i].aabb))
            renderDataCount--;
    }

    return ret;
}

}  // namespace red
