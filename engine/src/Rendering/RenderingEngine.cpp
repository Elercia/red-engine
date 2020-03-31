#include "RedEngine/Rendering/RenderingEngine.hpp"

#include "RedEngine/Debug/Logger/Logger.hpp"
#include "RedEngine/Rendering/Window.hpp"

namespace red
{
RenderingEngine::RenderingEngine()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        RED_LOG_ERROR("Error initializing SDL with error {}", SDL_GetError());
        SDL_Quit();
    }

    CreateNewWindow("Temp name");
}

RenderingEngine::~RenderingEngine()
{
    m_window.reset(nullptr);

    SDL_Quit();
}

void RenderingEngine::CreateNewWindow(std::string title)
{
    m_window = std::make_unique<Window>(std::move(title));
}

Window& RenderingEngine::GetWindow() { return *m_window; }

}  // namespace red
