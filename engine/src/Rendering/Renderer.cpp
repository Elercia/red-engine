#include "RedEngine/Rendering/Renderer.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Core/Configuration/CVar.hpp"
#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"
#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/Renderable.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/RenderDebugUtils.hpp"
#include "RedEngine/Rendering/Resource/Material.hpp"
#include "RedEngine/Rendering/Resource/ShaderProgram.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"
#include "RedEngine/Utils/Types.hpp"

// clang-format off
#include <GL/gl3w.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>
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

CVar<bool> s_enableCulling("EnableCulling", "Rendering", true);

Renderer::Renderer()
    : m_glContext(nullptr)
    , m_window(nullptr)
    , m_renderingData()
    , m_perInstanceData(1, sizeof(PerInstanceData))
    , m_perCameraData(1, sizeof(PerCameraData))
{
}

Renderer::~Renderer()
{
}

void Renderer::InitRenderer(WindowComponent* window)
{
    RED_LOG_INFO("Init OpenGL renderer");

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
    {
        RED_LOG_ERROR("Error initializing SDL_Video with error {}", SDL_GetError());
        SDL_Quit();
        RedAbort("Cannot initialize Renderer");
    }

    constexpr int OpenglMajorVersion = 4;
    constexpr int OpenglMinorVersion = 5;

    // Request OpenGL 4.5 context.
    CheckGLReturnValue(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OpenglMajorVersion),
                       "Error setting gl context major version with error {}", SDL_GetError());
    CheckGLReturnValue(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OpenglMinorVersion),
                       "Error setting gl context minor version with error {}", SDL_GetError());

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = window;
    m_window->CreateNewWindow();

    m_glContext = SDL_GL_CreateContext(window->GetSDLWindow());
    if (m_glContext == nullptr)
    {
        RED_LOG_ERROR(
            "Failed to query openGL context from SDL. Maybe the required Opengl version is not supported ({}.{}",
            OpenglMajorVersion, OpenglMinorVersion);
        return;
    }

    SDL_GL_MakeCurrent(m_window->GetSDLWindow(), m_glContext);

    if (gl3wInit() != 0)
    {
        RED_LOG_ERROR("Failed to init opengl functions");
        return;
    }

#ifdef RED_DEBUG
    // During init, enable debug output
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(OpenGLMessageCallback, nullptr);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(m_window->GetSDLWindow(), m_glContext);
    ImGui_ImplOpenGL3_Init("#version 130");
#endif

    m_perInstanceData.Init();
    m_perCameraData.Init();
}

void Renderer::ReCreateWindow(WindowComponent* /*window*/)
{
    // TODO recreate frame buffer etc
}

void Renderer::Finalise()
{
    m_perInstanceData.Finalize();
    m_perCameraData.Finalize();

#ifdef RED_DEBUG
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
#endif

    SDL_GL_DeleteContext(m_glContext);

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void Renderer::BeginRenderFrame()
{
    auto windowInfo = m_window->GetWindowInfo();
    glViewport(0, 0, windowInfo.width, windowInfo.height);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifdef RED_DEBUG
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
#endif
}

void Renderer::EndRenderFrame()
{
    m_renderingData.clear();

    SDL_GL_SwapWindow(m_window->GetSDLWindow());
}

void Renderer::BeginCameraRendering(CameraComponent* cameraComponent)
{
    // Setup the camera viewport
    auto viewport = cameraComponent->GetWindowRect();

    glViewport(viewport.x, viewport.y, viewport.width, viewport.height);

    glClearColor(cameraComponent->m_cleanColor.r / 255.f, cameraComponent->m_cleanColor.g / 255.f,
                 cameraComponent->m_cleanColor.b / 255.f, cameraComponent->m_cleanColor.a / 255.f);

    CullRenderDataForCamera(cameraComponent);
}

void Renderer::EndCameraRendering(CameraComponent* /*camera*/)
{
    m_culledAndSortedRenderingData.clearAndFree();
}

void Renderer::Draw(const Renderable* renderable, const Transform* transform)
{
    RenderingData data;
    data.geometry = &(renderable->m_geometry->m_geom);
    data.materialInstance = renderable->m_material;
    data.worldMatrix = transform->GetWorldMatrix();
    data.aabb = renderable->m_aabb;
    data.size = renderable->m_size;
    data.renderLayerIndex = renderable->m_layerIndex;
    data.type = renderable->m_material.material->GetRenderType();

    m_renderingData.push_back(std::move(data));
}

void Renderer::DrawDebugLine(const Vector2& first, const Vector2& second, const Color& color)
{
    m_debugLines.push_back(first);
    m_debugLines.push_back(second);

    m_debugLineColors.push_back(color);
}

void Renderer::DrawDebugCircle(const Vector2& /*center*/, float /*radius*/,
                               const Color& /*color*/ /*= ColorConstant::RED*/)
{
}

void Renderer::DrawDebugPoint(const Vector2& coord, const Color& color /*= ColorConstant::RED*/)
{
    DrawDebugCircle(coord, 0.1f, color);
}

void Renderer::RenderLayerOpaque(RenderLayerIndex layerIndex, CameraComponent* camera)
{
    RenderPassDesc desc;
    desc.alphaBlending = false;
    desc.name = "opaque";
    desc.renderType = RenderEntityType::Opaque;
    desc.layerIndex = layerIndex;

    RenderPass(camera, desc);
}

void Renderer::RenderLayerTransparency(RenderLayerIndex layerIndex, CameraComponent* camera)
{
    RenderPassDesc desc;
    desc.alphaBlending = true;
    desc.name = "transparency";
    desc.renderType = RenderEntityType::Transparency;
    desc.layerIndex = layerIndex;

    RenderPass(camera, desc);
}

void Renderer::RenderPass(CameraComponent* camera, const RenderPassDesc& desc)
{
    auto& toRender = m_renderingDataPerLayer[desc.layerIndex];

    if (toRender.empty())
        return;

    PROFILER_EVENT_CATEGORY(desc.name, ProfilerCategory::Rendering);

    glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, desc.name);

    if (desc.alphaBlending)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else
    {
        glDisable(GL_BLEND);
    }

    // Do the actual render calls to the camera render target
    for (uint32 i = 0; i < toRender.size(); i++)
    {
        auto& renderData = toRender[i];

        RedAssert(desc.layerIndex == renderData.renderLayerIndex);

        UseMaterial(renderData.materialInstance);
        UseGeometry(renderData.geometry);

        FillCameraBuffer(*camera);
        FillEntityBuffer(renderData);

        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_perCameraData.m_gpuBufferHandle);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_perInstanceData.m_gpuBufferHandle);

        auto primitiveType = renderData.geometry->GetPrimitiveType();

        glDrawElements(PrimitiveTypesAsGLTypes[(int) primitiveType], renderData.geometry->GetIndexeCount(),
                       GL_UNSIGNED_INT, nullptr);
    }

    glPopDebugGroup();
}

void Renderer::RenderDebug(CameraComponent* /*camera*/)
{
    m_debugLines.clear();
    m_debugLineColors.clear();
}

void Renderer::RenderGlobalDebug()
{
    glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, "Render debug");

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glPopDebugGroup();
}

void Renderer::FillCameraBuffer(const CameraComponent& camera)
{
    PerCameraData* perCamera = m_perCameraData.Map<PerCameraData>(MapType::WRITE);
    perCamera->viewProj = camera.GetViewProj();
    m_perCameraData.UnMap();
}

void Renderer::FillEntityBuffer(const RenderingData& data)
{
    PerInstanceData* perInstance = m_perInstanceData.Map<PerInstanceData>(MapType::WRITE);
    perInstance->world = data.worldMatrix;
    perInstance->size = data.size;
    perInstance->padding = 1.f;
    m_perInstanceData.UnMap();
}

void Renderer::UseMaterial(const MaterialInstance& materialInstance)
{
    const auto& material = materialInstance.material;
    const auto& defaultBindings = material->m_defaultBindings.bindings;
    const auto& overiddenBindings = materialInstance.overiddenBindings.bindings;

    // FIXME fix crash when a invalid handle is used
    glUseProgram(material->GetShaderProgram()->m_handle);

    // Bind textures and buffers
    for (int i = 0; i < BindingIndex::Max; i++)
    {
        const BindingValue* value = nullptr;

        const auto& defaultBinding = defaultBindings[i];
        const auto& overidenBinding = overiddenBindings[i];
        if (overidenBinding.type != BindingType::Undefined)
        {
            value = &overidenBinding;
        }
        else if (defaultBinding.type != BindingType::Undefined)
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
                glUniform4f(i, vector[0], vector[1], vector[2], vector[3]);
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

void Renderer::CullRenderDataForCamera(CameraComponent* camera)
{
    PROFILER_EVENT_CATEGORY("Renderer::CullRenderDataForCamera", ProfilerCategory::Rendering);
    RedAssert(m_culledAndSortedRenderingData.empty(),
              "The camera data is not empty. Maybe EndCameraRendering has not been called");

    for (RenderingData& data : m_renderingData)
    {
        if (!s_enableCulling || camera->IsVisibleFrom(data.aabb))
        {
            m_culledAndSortedRenderingData.push_back(data);
        }
    }

    std::sort(m_culledAndSortedRenderingData.begin(), m_culledAndSortedRenderingData.end(),
              [](auto& l, auto& r) { return l.renderLayerIndex < r.renderLayerIndex && l.type < r.type; });

    uint32 renderLayerIndex = 0;
    uint32 start = 0;
    uint32 count = 0;
    for (uint32 i = 0; i < m_culledAndSortedRenderingData.size(); i++)
    {
        if (m_culledAndSortedRenderingData[i].renderLayerIndex != renderLayerIndex)
        {
            count = i - start;

            m_renderingDataPerLayer[renderLayerIndex] = ArrayView(m_culledAndSortedRenderingData, start, count);

            start = i;
            renderLayerIndex++;
        }
    }

    m_renderingDataPerLayer[renderLayerIndex] =
        ArrayView(m_culledAndSortedRenderingData, start, m_culledAndSortedRenderingData.size() - start);

    renderLayerIndex++;

    for (int i = renderLayerIndex; i < 32; i++)
    {
        m_renderingDataPerLayer[i] = ArrayView(m_culledAndSortedRenderingData, 0, 0);
    }
}

}  // namespace red
