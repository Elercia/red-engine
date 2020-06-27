
#include "RedEngine/Debug/Debug.hpp"
#include "RedEngine/Debug/Logger/Logger.hpp"
#include "RedEngine/Rendering/RenderingEngine.hpp"
#include "RedEngine/Rendering/Window.hpp"
#include "RedEngine/Rendering/Texture2D.hpp"
#include "RedEngine/Core/Components/Sprite.hpp"
#include <RedEngine/Rendering/Component/CameraComponent.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>

#include <SDL2/SDL_image.h>

namespace red
{
RenderingEngine::RenderingEngine() {}

RenderingEngine::~RenderingEngine()
{
    if (m_renderer != nullptr)
        SDL_DestroyRenderer(m_renderer);

    m_window.reset(nullptr);

    SDL_Quit();
}

void RenderingEngine::CreateNewWindow() { m_window = std::make_unique<Window>(); }

Window& RenderingEngine::GetWindow() { return *m_window; }

void RenderingEngine::InitRenderer()
{
    m_renderer = SDL_CreateRenderer(m_window->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED);

    if (m_renderer == nullptr)
    {
        RED_LOG_ERROR("Error initializing renderer with error {}", SDL_GetError());
        SDL_Quit();
        RED_ABORT("Cannot initialize Renderer");
    }

    RED_LOG_INFO("Init Renderer");
}

void RenderingEngine::BeginRenderFrame() {}

void RenderingEngine::EndRenderFrame() { SDL_RenderPresent(m_renderer); }

void RenderingEngine::BeginCameraRendering(CameraComponent* cameraComponent)
{
    // Setup the camera viewport
    SDL_Rect viewport = {static_cast<int>(cameraComponent->m_viewport.x),
                         static_cast<int>(cameraComponent->m_viewport.y),
                         static_cast<int>(cameraComponent->m_viewport.width),
                         static_cast<int>(cameraComponent->m_viewport.height)};

    SDL_RenderSetViewport(m_renderer, &viewport);

    // Set the camera draw color
    SDL_SetRenderDrawColor(
        m_renderer, cameraComponent->m_backgroundColor.r, cameraComponent->m_backgroundColor.g,
        cameraComponent->m_backgroundColor.b, cameraComponent->m_backgroundColor.a);

    SDL_RenderClear(m_renderer);

    //    if (cameraComponent->m_renderedTexture == nullptr)
    //    {
    //        auto info = m_window->GetWindowInfo();
    //
    //        auto* sdlTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
    //                                             SDL_TEXTUREACCESS_TARGET, info.width,
    //                                             info.height);
    //
    //        cameraComponent->m_renderedTexture = ResourceEngine::CreateTextureFrom(sdlTexture);
    //    }
    //
    //    SDL_SetRenderTarget(m_renderer, cameraComponent->m_renderedTexture->m_sdlTexture);
}

void RenderingEngine::EndCameraRendering()
{
    //    // Reset the viewport
    //    auto info = m_window->GetWindowInfo();
    //    SDL_Rect viewport = {0, 0, info.width, info.height};
    //
    //    SDL_RenderSetViewport(m_renderer, &viewport);
    //
    //    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    //
    //    SDL_SetRenderTarget(m_renderer, nullptr);
}

SDL_Renderer* RenderingEngine::GetRenderer() { return m_renderer; }

void RenderingEngine::Render(CameraComponent* camera, Sprite* sprite, const Transform& transform)
{
    if (sprite->m_texture->GetLoadState() == LoadState::STATE_LOADED)
    {
        const auto& position = camera->WorldToViewportPoint(transform.GetPosition());

        SDL_Rect dest{static_cast<int>(position.x), static_cast<int>(position.y),
                      sprite->m_texture->m_textureSize.w, sprite->m_texture->m_textureSize.h};

        SDL_RenderCopy(m_renderer, sprite->m_texture->m_sdlTexture, nullptr, &dest);
    }
}

void RenderingEngine::DrawLine(Vector2 first, Vector2 second, Color color)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(m_renderer, static_cast<int>(first.x), static_cast<int>(first.y),
                       static_cast<int>(second.x), static_cast<int>(second.y));
}

void RenderingEngine::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        RED_LOG_ERROR("Error initializing SDL with error {}", SDL_GetError());
        SDL_Quit();
        RED_ABORT("Cannot initialize SDL2");
    }

    int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if (IMG_Init(flags) != flags)
    {
        RED_LOG_ERROR("Error initializing SDL image with error {}", IMG_GetError());
        IMG_Quit();
        SDL_Quit();
        RED_ABORT("Cannot initialize SDL image");
    }

    CreateNewWindow();

    InitRenderer();
}

}  // namespace red
