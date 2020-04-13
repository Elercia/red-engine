#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

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
    bgfx::shutdown();

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

    bgfx::PlatformData pd;
#if BX_PLATFORM_LINUX
    pd.ndt = m_window->GetNativeDisplay();
    pd.nwh = (void*) (uintptr_t) m_window->GetNativeHandle();
#elif BX_PLATFORM_WINDOWS
    pd.ndt = NULL;
    pd.nwh = m_window->GetNativeHandle();
#endif  // BX_PLATFORM_
    pd.context = NULL;
    pd.backBuffer = NULL;
    pd.backBufferDS = NULL;

    bgfx::Init init;
    init.type = bgfx::RendererType::OpenGL;
    init.vendorId = BGFX_PCI_ID_NONE;
    init.resolution.width = windowInfo.width;
    init.resolution.height = windowInfo.height;
    init.resolution.reset = BGFX_RESET_VSYNC;
    init.platformData = pd;
    bgfx::init(init);

    // Enable debug text.
    bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

    // Set view 0 clear state.
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xff3030ff, 1.0f, 0);
}

}  // namespace red
