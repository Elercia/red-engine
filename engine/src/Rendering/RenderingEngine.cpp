#include "RedEngine/Debug/Debug.hpp"
#include "RedEngine/Debug/Logger/Logger.hpp"
#include "RedEngine/Rendering/RenderingEngine.hpp"
#include "RedEngine/Rendering/Window.hpp"

namespace red
{
RenderingEngine::RenderingEngine()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        //        RED_LOG_ERROR("Error initializing SDL with error {}", SDL_GetError());
        std::cout << "Error initializing SDL with error " << SDL_GetError() << std::endl;
        SDL_Quit();
        RED_ABORT("Cannot initialize SDL2");
    }

    CreateNewWindow("Temp name");

    InitRenderingLibrary();
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

void RenderingEngine::InitRenderingLibrary()
{
    auto windowInfo = m_window->GetWindowInfo();

}

}  // namespace red
