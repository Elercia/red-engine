
#include <RedEngine/Core/Debug/DebugMacros.hpp>
#include <RedEngine/Core/Debug/Logger/Logger.hpp>
#include <RedEngine/Rendering/RenderingEngine.hpp>
#include <RedEngine/Rendering/Window.hpp>
#include <RedEngine/Rendering/Texture2D.hpp>
#include <RedEngine/Core/Components/Sprite.hpp>
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
    auto& currentAnimation = *sprite->m_currentAnimationInfo.currentAnimation;

    if (currentAnimation.texture &&
        currentAnimation.texture->GetLoadState() == LoadState::STATE_LOADED)
    {
        const auto& position = camera->WorldToViewportPoint(transform.GetPosition());

        auto& currentAnimationFrame = *sprite->m_currentAnimationInfo.currentAnimationFrame;

        SDL_Rect source{currentAnimationFrame.rect.x, currentAnimationFrame.rect.y,
                        currentAnimationFrame.rect.width, currentAnimationFrame.rect.height};
        SDL_Rect dest{static_cast<int>(position.x), static_cast<int>(position.y),
                      currentAnimationFrame.size.x, currentAnimationFrame.size.y};

        SDL_Point center{currentAnimationFrame.center.x, currentAnimationFrame.center.y};

        SDL_RendererFlip flip = (SDL_RendererFlip)(
            SDL_FLIP_NONE | (currentAnimationFrame.flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) |
            (currentAnimationFrame.flipV ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE));

        SDL_RenderCopyEx(m_renderer, currentAnimation.texture->m_sdlTexture, &source, &dest,
                           currentAnimationFrame.rotation, &center, flip);
    }
}

void RenderingEngine::DrawLine(CameraComponent* camera, const Vector2& first, const Vector2& second,
                               const Color& color)
{
    const auto& fPos = camera->WorldToViewportPoint(first);
    const auto& sPos = camera->WorldToViewportPoint(second);

    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(m_renderer, (int) (fPos.x), (int) (fPos.y), (int) (sPos.x), (int) (sPos.y));
}

void RenderingEngine::DrawLines(CameraComponent* camera, const std::vector<Vector2>& points,
                                const Color& color /*= ColorConstant::RED*/,
                                bool isFilled /*= false*/)
{
    std::vector<SDL_Point> sdlPoints;
    sdlPoints.reserve(points.size());
    for (const Vector2& p : points)
    {
        const auto& v = camera->WorldToViewportPoint(p);

        sdlPoints.push_back({(int) v.x, (int) v.y});
    }

    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLines(m_renderer, sdlPoints.data(), (int)sdlPoints.size());
}

void RenderingEngine::DrawCircle(CameraComponent* camera, const Vector2& center, float radius,
                                 const Color& color /*= ColorConstant::RED*/)
{
    const auto& pos = camera->WorldToViewportPoint(center);

    SDL_Rect rect{(int) (pos.x - radius), (int) (pos.y - radius), (int) (pos.x + radius),
                  (int) (pos.y + radius)};
    SDL_RenderDrawRect(m_renderer, &rect);
}

void RenderingEngine::DrawPoint(CameraComponent* camera, const Vector2& coord,
                                const Color& color /*= ColorConstant::RED*/)
{
    const auto& pos = camera->WorldToViewportPoint(coord);

    SDL_RenderDrawPoint(m_renderer, (int) pos.x, (int) pos.y);
}

void RenderingEngine::Init(const EngineInitDesc& initDesc)
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
