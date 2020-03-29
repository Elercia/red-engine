#include <bgfx/bgfx.h>

#include <RedEngine/Window.hpp>
#include <RedEngine/engine/RenderingEngine.hpp>
#include <debug/Debug.hpp>

namespace red
{
RenderingEngine::RenderingEngine()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        RED_ABORT("Error")
    }
}

RenderingEngine::~RenderingEngine() { SDL_Quit(); }

void RenderingEngine::InitializeWindow(Window* window) {

    bgfx::PlatformData pd;
    pd.nwh = window->;
    bgfx::setPlatformData(pd);

    bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
    bgfxInit.resolution.width = WNDW_WIDTH;
    bgfxInit.resolution.height = WNDW_HEIGHT;
    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
    bgfx::init(bgfxInit);
}

void RenderingEngine::WindowResizeCallBack(uint32_t width, uint32_t height) {}

}  // namespace red
