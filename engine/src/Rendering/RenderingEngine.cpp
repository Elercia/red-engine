#include "RedEngine/Debug/Debug.hpp"
#include "RedEngine/Debug/Logger/Logger.hpp"
#include "RedEngine/Rendering/RenderingEngine.hpp"
#include "RedEngine/Rendering/Window.hpp"
#include "RedEngine/Rendering/Texture2D.hpp"
#include "RedEngine/Core/Components/Sprite.hpp"
#include <RedEngine/Resources/Resource.hpp>

#include <SDL2/SDL_render.h>
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

void RenderingEngine::BeginRenderFrame()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
}
void RenderingEngine::EndRenderFrame() { SDL_RenderPresent(m_renderer); }

SDL_Renderer* RenderingEngine::GetRenderer() { return m_renderer; }

void RenderingEngine::Render(Sprite* sprite, const Transform& transform)
{
    if (sprite->m_texture->GetLoadState() == LoadState::STATE_LOADED)
    {
        const auto& position = transform.GetPosition();

        SDL_Rect dest{static_cast<int>(position.m_x), static_cast<int>(position.m_y),
                      sprite->m_texture->m_textureSize.w, sprite->m_texture->m_textureSize.h};

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
