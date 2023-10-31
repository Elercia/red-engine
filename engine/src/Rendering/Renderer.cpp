#include "RedEngine/Rendering/Renderer.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Core/Configuration/CVar.hpp"
#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/Renderable.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/RenderDebugUtils.hpp"
#include "RedEngine/Rendering/Resource/Material.hpp"
#include "RedEngine/Rendering/Resource/ShaderProgram.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"
#include "RedEngine/Rendering/Text.hpp"
#include "RedEngine/Utils/Types.hpp"

// clang-format off
#include <GL/gl3w.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>
#include <RedEngine/Resources/ResourceHolderComponent.hpp>
#include <RedEngine/Rendering/Resource/MaterialResourceLoader.hpp>
// clang-format on

#define CheckGLReturnValue(expr, ...) \
    if ((expr) != 0)                  \
    {                                 \
        RED_LOG_ERROR(__VA_ARGS__);   \
    }

namespace red
{
GLenum PrimitiveTypesAsGLTypes(PrimitiveType type)
{
    switch (type)
    {
        case PrimitiveType::TRIANGLE:
            return GL_TRIANGLES;
        case PrimitiveType::LINES:
            return GL_LINES;
        case PrimitiveType::POINTS:
            return GL_POINTS;
    }

    RedAssertNotReached();

    return GL_TRIANGLES;
}

CVar<bool> s_enableCulling("EnableCulling", "Rendering", true);

Renderer::Renderer()
    : m_glContext(nullptr)
    , m_window(nullptr)
    , m_renderingData()
    , m_perInstanceData(1, sizeof(PerInstanceData))
    , m_perCameraData(1, sizeof(PerCameraData))
    , m_lineVertexColorVBO(0)
    , m_lineVAO(0)
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

#ifdef RED_DEVBUILD
    // During init, enable debug output
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback((GLDEBUGPROC) &red::OpenGLMessageCallback, nullptr);

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

    // Create the VBO & VAO for the debug draw primitive
    glGenVertexArrays(1, &m_lineVAO);
    glBindVertexArray(m_lineVAO);

    glGenBuffers(1, &m_lineVertexColorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_lineVertexColorVBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);  // TODO: Change this to vec2

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (4 * sizeof(float)));

    m_textMaterial = m_window->GetWorld()
                         ->GetWorldComponent<ResourceHolderComponent>()
                         ->GetResourceLoader<MaterialResourceLoader>()
                         ->LoadResource(Path::Resource("ENGINE_RESOURCES/FONT_MATERIAL"));
}

void Renderer::ReCreateWindow(WindowComponent* /*window*/)
{
    // TODO recreate frame buffer etc if needed
}

void Renderer::Finalise()
{
    m_perInstanceData.Finalize();
    m_perCameraData.Finalize();

#ifdef RED_DEVBUILD
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
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifdef RED_DEVBUILD
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
#endif
}

void Renderer::EndRenderFrame()
{
    PROFILER_EVENT_CATEGORY("Renderer::EndRenderFrame", ProfilerCategory::Rendering);

    m_renderingData.clear();

    SDL_GL_SwapWindow(m_window->GetSDLWindow());
}

void Renderer::BeginCameraRendering(CameraComponent* cameraComponent)
{
    // Setup the camera viewport
    auto viewport = cameraComponent->GetWindowRect();

    glViewport(viewport.x, viewport.y, viewport.width, viewport.height);

    glClearColor(cameraComponent->m_cleanColor.r, cameraComponent->m_cleanColor.g, cameraComponent->m_cleanColor.b,
                 cameraComponent->m_cleanColor.a);

    CullRenderDataForCamera(cameraComponent);
}

void Renderer::Draw(Text* text, const Transform* transform)
{
    if (text->m_dirty)
        CreateText(text);

    text->m_material.material = m_textMaterial;
    BindingValue& bindingAtlas = text->m_material.overriddenBindings.bindings[BindingIndex::Diffuse];
    bindingAtlas.type = BindingType::Texture;
    bindingAtlas.texture = text->m_font->m_atlas.get();

    BindingValue& bindingFontSize = text->m_material.overriddenBindings.bindings[BindingIndex::FontSize];
    bindingFontSize.type = BindingType::Vector4;
    bindingFontSize.floats[0] =
        ((float) text->m_fontSize / (float) text->m_font->m_size) * (float) text->m_font->m_pixelRange;

    RenderingData data;
    data.geometry = &text->m_geometry;
    data.materialInstance = text->m_material;
    data.worldMatrix = transform->GetWorldMatrix();
    data.aabb = AABB(Vector2(-1000, -1000), Vector2(100000, 100000));  // TODO
    data.size = Vector2(text->m_fontSize, text->m_fontSize);
    data.renderLayerIndex = text->m_layerIndex;
    data.type = text->m_material.material->GetRenderType();

    m_renderingData.push_back(std::move(data));
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

void Renderer::RenderSprites(CameraComponent* camera)
{
    if (m_cameraRenderingData.empty())
        return;

    PROFILER_EVENT_CATEGORY("RenderSprites", ProfilerCategory::Rendering);

    glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, "RenderSprites");

    // TODO ?
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Do the actual render calls to the camera render target
    for (uint32 i = 0; i < m_cameraRenderingData.size(); i++)
    {
        auto& renderData = m_cameraRenderingData[i];

        UseMaterial(renderData.materialInstance);
        UseGeometry(renderData.geometry);

        FillCameraBuffer(*camera);
        FillEntityBuffer(renderData);

        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_perCameraData.m_gpuBufferHandle);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_perInstanceData.m_gpuBufferHandle);

        auto primitiveType = renderData.geometry->GetPrimitiveType();
        glDrawElements(PrimitiveTypesAsGLTypes(primitiveType), renderData.geometry->GetIndexeCount(), GL_UNSIGNED_INT,
                       nullptr);
    }

    glPopDebugGroup();
}

void Renderer::RenderDebug(CameraComponent* camera, DebugComponent* debug)
{
    auto shader = debug->GetLineShader();
    const auto& lines = debug->GetDebugLines();

    if (lines.empty())
        return;

    glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, "Render debug lines");
    PROFILER_EVENT_CATEGORY("Renderer::RenderDebug", ProfilerCategory::Rendering);

    glDisable(GL_DEPTH_TEST);

    glUseProgram(shader->m_handle);

    glNamedBufferData(m_lineVertexColorVBO, lines.size() * sizeof(DebugLinePoint), lines.data(), GL_STATIC_DRAW);

    FillCameraBuffer(*camera);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_perCameraData.m_gpuBufferHandle);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(m_lineVAO);

    glDrawArrays(GL_LINES, 0, lines.size());

    glPopDebugGroup();
}

void Renderer::RenderFullScreenDebugUI()
{
    glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, "Render debug UI");
    PROFILER_EVENT_CATEGORY("Renderer::RenderDebugUI", ProfilerCategory::Rendering);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glPopDebugGroup();
}

void Renderer::FillCameraBuffer(const CameraComponent& camera)
{
    PerCameraData data;
    data.viewProj = camera.GetViewProj();

    glNamedBufferSubData(m_perCameraData.m_gpuBufferHandle, 0, sizeof(PerCameraData), &data);
}

void Renderer::FillEntityBuffer(const RenderingData& data)
{
    PerInstanceData instanceData;
    instanceData.world = data.worldMatrix;
    instanceData.size = data.size;
    instanceData.renderLayer = (float) data.renderLayerIndex;

    glNamedBufferSubData(m_perInstanceData.m_gpuBufferHandle, 0, sizeof(PerInstanceData), &instanceData);
}

void Renderer::CreateText(Text* text)
{
    // Reset the text rendering data
    text->m_geometry.Destroy();
    text->m_dirty = false;

    // There is no text to render
    if (text->m_textStr.empty() || text->m_font->GetLoadState() != LoadState::STATE_LOADED)
    {
        return;
    }

    // We need one quad for each letter. We can't share vertices per quads so indices count is vertices count
    const uint32 vertexCount = 4 * (uint32) text->m_textStr.size();
    const uint32 indexCount = 6 * (uint32) text->m_textStr.size();

    Array<Vector3, DoubleLinearArrayAllocator> vertices;  // TODO Vector2
    vertices.reserve(vertexCount);
    Array<Vector2, DoubleLinearArrayAllocator> uvs;
    uvs.reserve(vertexCount);
    Array<int, DoubleLinearArrayAllocator> indices;
    indices.reserve(indexCount);

    float originX = 0.f;

    // Go through all the chars from the text and create the vertices and indices
    for (char c : text->m_textStr)
    {
        GlyphMap::const_iterator glyphIt = text->m_font->m_glyphs.find(c);

        {
            auto topLeft = 0;
            auto topRight = 1;
            auto bottomLeft = 2;
            auto bottomRight = 3;

            // First triangle
            indices.push_back(vertices.size() + topLeft);
            indices.push_back(vertices.size() + topRight);
            indices.push_back(vertices.size() + bottomLeft);

            // Second triangle
            indices.push_back(vertices.size() + topRight);
            indices.push_back(vertices.size() + bottomRight);
            indices.push_back(vertices.size() + bottomLeft);
        }

        if (glyphIt == text->m_font->m_glyphs.end())
        {
            const Vector3 topLeft = {originX + 0.f, -text->m_fontSize / 2.f, 0.f};
            const Vector3 topRight = {originX + text->m_fontSize, -text->m_fontSize / 2.f, 0.f};
            const Vector3 bottomLeft = {originX + 0.f, text->m_fontSize / 2.f, 0.f};
            const Vector3 bottomRight = {originX + text->m_fontSize, text->m_fontSize / 2.f, 0.f};

            // Push the quad vertices positions
            vertices.push_back(topLeft);
            vertices.push_back(topRight);
            vertices.push_back(bottomLeft);
            vertices.push_back(bottomRight);

            // Push the quad uvs
            uvs.push_back({0.f, 0.f});
            uvs.push_back({0.f, 0.f});
            uvs.push_back({0.f, 0.f});
            uvs.push_back({0.f, 0.f});
            continue;
        }

        const Glyph& glyph = glyphIt->second;

        {
            const float bottom = glyph.planeBounds.x;
            const float left = glyph.planeBounds.y;
            const float top = glyph.planeBounds.z;
            const float right = glyph.planeBounds.w;

            const Vector3 topLeft = Vector3(originX + left, -top, 0.f) * (float) text->m_font->m_size;
            const Vector3 topRight = Vector3(originX + right, -top, 0.f) * (float) text->m_font->m_size;
            const Vector3 bottomLeft = Vector3(originX + left, -bottom, 0.f) * (float) text->m_font->m_size;
            const Vector3 bottomRight = Vector3(originX + right, -bottom, 0.f) * (float) text->m_font->m_size;

            // Push the quad vertices positions
            vertices.push_back(topLeft);
            vertices.push_back(topRight);
            vertices.push_back(bottomLeft);
            vertices.push_back(bottomRight);
        }

        {
            const float top = glyph.atlasBounds.x;
            const float left = glyph.atlasBounds.y;
            const float bottom = glyph.atlasBounds.z;
            const float right = glyph.atlasBounds.w;

            const Vector2 topLeft = {top, left};
            const Vector2 topRight = {top, right};
            const Vector2 bottomLeft = {bottom, left};
            const Vector2 bottomRight = {bottom, right};

            // Push the quad uvs positions
            uvs.push_back(topLeft);
            uvs.push_back(topRight);
            uvs.push_back(bottomLeft);
            uvs.push_back(bottomRight);
        }

        originX += glyph.advance;
    }
    text->m_geometry.Create(vertexCount, (float*) vertices.data(), (float*) uvs.data(), indexCount, indices.data(),
                            PrimitiveType::TRIANGLE);
}

void Renderer::UseMaterial(const MaterialInstance& materialInstance)
{
    const auto& material = materialInstance.material;
    const auto& defaultBindings = material->m_defaultBindings.bindings;
    const auto& overriddenBindings = materialInstance.overriddenBindings.bindings;

    // FIXME fix crash when a invalid handle is used
    glUseProgram(material->GetShaderProgram()->m_handle);

    // Bind textures and buffers
    for (int i = 0; i < BindingIndex::Max; i++)
    {
        const BindingValue* value = nullptr;

        const auto& defaultBinding = defaultBindings[i];
        const auto& overriddenBinding = overriddenBindings[i];
        if (overriddenBinding.type != BindingType::Undefined)
        {
            value = &overriddenBinding;
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
    glEnableVertexAttribArray(1);
    glBindVertexArray(geom->m_vaoHandle);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geom->m_iboHandle);
}

void Renderer::CullRenderDataForCamera(CameraComponent* camera)
{
    PROFILER_EVENT_CATEGORY("Renderer::CullRenderDataForCamera", ProfilerCategory::Rendering);
    RedAssert(m_cameraRenderingData.empty(),
              "The camera data is not empty. Maybe EndCameraRendering has not been called");

    if (s_enableCulling)
    {
        for (RenderingData& data : m_renderingData)
        {
            if (camera->IsVisibleFrom(data.aabb))
            {
                m_cameraRenderingData.push_back(data);
            }
        }
    }
    else
    {
        for (RenderingData& data : m_renderingData)
        {
            m_cameraRenderingData.push_back(data);
        }
    }
}

void Renderer::EndCameraRendering(CameraComponent* /*camera*/)
{
    PROFILER_EVENT_CATEGORY("Renderer::EndCameraRendering", ProfilerCategory::Rendering);
    m_cameraRenderingData.clearAndFree();
}

}  // namespace red
