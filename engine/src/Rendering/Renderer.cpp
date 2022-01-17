#include "RedEngine/Rendering/Renderer.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/Renderable.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"

// clang-format off
#include <GL/gl3w.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
// clang-format on

namespace red
{
Renderer::Renderer() : m_glContext(nullptr), m_window(nullptr)
{
}

Renderer::~Renderer()
{
}

void Renderer::InitRenderer(WindowComponent* window)
{
    m_window = window;
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

    RED_LOG_INFO("Init OpenGL renderer");
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
    SDL_GL_SwapWindow(m_window->GetSDLWindow());
}

void Renderer::BeginCameraRendering(CameraComponent* cameraComponent)
{
    // Setup the camera viewport
    glViewport(cameraComponent->m_viewport.x, cameraComponent->m_viewport.y, cameraComponent->m_viewport.width,
               cameraComponent->m_viewport.height);

    glClearColor(cameraComponent->m_cleanColor.r / 255.f, cameraComponent->m_cleanColor.g / 255.f,
                 cameraComponent->m_cleanColor.b / 255.f, cameraComponent->m_cleanColor.a / 255.f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::EndCameraRendering()
{
}

void Renderer::Render(CameraComponent* /*camera*/, Renderable* /*renderable*/, const Transform& /*transform*/)
{
    // TODO
}

void Renderer::DrawLine(CameraComponent* /*camera*/, const Vector2& /*first*/, const Vector2& /*second*/,
                        const Color& /*color*/)
{
}

void Renderer::DrawLines(CameraComponent* /*camera*/, const Array<Vector2>& /*points*/,
                         const Color& /*color*/ /*= ColorConstant::RED*/,
                         bool /*isFilled*/ /*= false*/)  // TODO isFilled
{
}

void Renderer::DrawCircle(CameraComponent* /*camera*/, const Vector2& /*center*/, float /*radius*/,
                          const Color& /*color*/ /*= ColorConstant::RED*/)  // TODO color
{
}

void Renderer::DrawPoint(CameraComponent* /*camera*/, const Vector2& /*coord*/,
                         const Color& /*color*/ /*= ColorConstant::RED*/)  // TODO color
{
}

}  // namespace red
