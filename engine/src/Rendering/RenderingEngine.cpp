#include "RedEngine/Debug/Debug.hpp"
#include "RedEngine/Debug/Logger/Logger.hpp"
#include "RedEngine/Rendering/RenderingEngine.hpp"
#include "RedEngine/Rendering/Window.hpp"
#include "RedEngine/Rendering/Texture2D.hpp"
#include "RedEngine/Core/Components/Sprite.hpp"

#include <SDL2/SDL_render.h>
#include <RedEngine/Resources/Resource.hpp>

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

void RenderingEngine::BeginRenderFrame()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
}
void RenderingEngine::EndRenderFrame() { SDL_RenderPresent(m_renderer); }

void RenderingEngine::DebugDrawRect()
{
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    auto windowInfo = m_window->GetWindowInfo();

    SDL_Rect rect;
    rect.h = 100;
    rect.w = 200;
    rect.x = (windowInfo.width / 2) - rect.w;
    rect.y = (windowInfo.height / 2) - rect.h;
    SDL_RenderDrawRect(m_renderer, &rect);
}

SDL_Renderer* RenderingEngine::GetRenderer() { return m_renderer; }

void RenderingEngine::Render(Sprite* sprite, const Transform& transform)
{
    if (sprite->m_texture->GetLoadState() == LoadState::STATE_LOADED)
    {
        auto position = transform.GetPosition();
        SDL_Rect dest{position.m_x, position.m_y, sprite->m_texture->m_textureSize.h,
                      sprite->m_texture->m_textureSize.w};

        SDL_RenderCopy(m_renderer, sprite->m_texture->m_sdlTexture, nullptr, &dest);
    }
}
void RenderingEngine::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        RED_LOG_ERROR("Error initializing SDL with error {}", SDL_GetError());
        SDL_Quit();
        RED_ABORT("Cannot initialize SDL2");
    }

    CreateNewWindow();

    InitRenderer();
}

}  // namespace red
