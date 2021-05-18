
#include "RedEngine/Rendering/Renderer.hpp"

#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/Sprite.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"

#include <SDL2/SDL_image.h>

namespace red
{
Renderer::Renderer() : m_renderer(nullptr) {}

Renderer::~Renderer()
{
    if (m_renderer != nullptr)
        SDL_DestroyRenderer(m_renderer);

    SDL_Quit();
}

void Renderer::InitRenderer(WindowComponent* window)
{
    m_renderer = SDL_CreateRenderer(window->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED);

    if (m_renderer == nullptr)
    {
        RED_LOG_ERROR("Error initializing renderer with error {}", SDL_GetError());
        SDL_Quit();
        RED_ABORT("Cannot initialize Renderer");
    }

    RED_LOG_INFO("Init Renderer");
}

void Renderer::BeginRenderFrame() {}

void Renderer::EndRenderFrame() { SDL_RenderPresent(m_renderer); }

void Renderer::BeginCameraRendering(CameraComponent* cameraComponent)
{
    // Setup the camera viewport
    SDL_Rect viewport = {
        static_cast<int>(cameraComponent->m_viewport.x), static_cast<int>(cameraComponent->m_viewport.y),
        static_cast<int>(cameraComponent->m_viewport.width), static_cast<int>(cameraComponent->m_viewport.height)};

    SDL_RenderSetViewport(m_renderer, &viewport);

    // Set the camera draw color
    SDL_SetRenderDrawColor(m_renderer, cameraComponent->m_backgroundColor.r, cameraComponent->m_backgroundColor.g,
                           cameraComponent->m_backgroundColor.b, cameraComponent->m_backgroundColor.a);

    SDL_RenderClear(m_renderer);
}

void Renderer::EndCameraRendering()
{
    
}

SDL_Renderer* Renderer::GetSDLRenderer() { return m_renderer; }

void Renderer::Render(CameraComponent* camera, Sprite* sprite, const Transform& transform)
{
    auto& currentAnimation = *sprite->m_currentAnimationInfo.currentAnimation;

    if (currentAnimation.texture && currentAnimation.texture->GetLoadState() == LoadState::STATE_LOADED)
    {
        const auto& position = camera->WorldToViewportPoint(transform.GetPosition());

        auto& currentAnimationFrame = *sprite->m_currentAnimationInfo.currentAnimationFrame;

        SDL_Rect source{currentAnimationFrame.rect.x, currentAnimationFrame.rect.y, currentAnimationFrame.rect.width,
                        currentAnimationFrame.rect.height};
        SDL_Rect dest{static_cast<int>(position.x), static_cast<int>(position.y), currentAnimationFrame.size.x,
                      currentAnimationFrame.size.y};

        SDL_Point center{currentAnimationFrame.center.x, currentAnimationFrame.center.y};

        SDL_RendererFlip flip =
            (SDL_RendererFlip)(SDL_FLIP_NONE | (currentAnimationFrame.flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) |
                               (currentAnimationFrame.flipV ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE));

        SDL_RenderCopyEx(m_renderer, currentAnimation.texture->m_sdlTexture, &source, &dest,
                         currentAnimationFrame.rotation, &center, flip);
    }
}

void Renderer::DrawLine(CameraComponent* camera, const Vector2& first, const Vector2& second, const Color& color)
{
    const auto& fPos = camera->WorldToViewportPoint(first);
    const auto& sPos = camera->WorldToViewportPoint(second);

    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(m_renderer, (int) (fPos.x), (int) (fPos.y), (int) (sPos.x), (int) (sPos.y));
}

void Renderer::DrawLines(CameraComponent* camera, const std::vector<Vector2>& points,
                                const Color& color /*= ColorConstant::RED*/,
                                bool /*isFilled*/ /*= false*/)  // TODO isFilled
{
    std::vector<SDL_Point> sdlPoints;
    sdlPoints.reserve(points.size());
    for (const Vector2& p : points)
    {
        const auto& v = camera->WorldToViewportPoint(p);

        sdlPoints.push_back({(int) v.x, (int) v.y});
    }

    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLines(m_renderer, sdlPoints.data(), (int) sdlPoints.size());
}

void Renderer::DrawCircle(CameraComponent* camera, const Vector2& center, float radius,
                                 const Color& /*color*/ /*= ColorConstant::RED*/)  // TODO color
{
    const auto& pos = camera->WorldToViewportPoint(center);

    SDL_Rect rect{(int) (pos.x - radius), (int) (pos.y - radius), (int) (radius * 2), (int) (radius * 2)};
    SDL_RenderDrawRect(m_renderer, &rect);
}

void Renderer::DrawPoint(CameraComponent* camera, const Vector2& coord,
                                const Color& /*color*/ /*= ColorConstant::RED*/)  // TODO color
{
    const auto& pos = camera->WorldToViewportPoint(coord);

    SDL_RenderDrawPoint(m_renderer, (int) pos.x, (int) pos.y);
}

}  // namespace red
