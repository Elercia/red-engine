#include <RedEngine/Window.hpp>
#include <RedEngine/debug/Debug.hpp>
#include <RedEngine/engine/RenderingEngine.hpp>

namespace red
{
RenderingEngine::RenderingEngine() {}
RenderingEngine::~RenderingEngine() {}

void RenderingEngine::InitializeEngine(Window* window)
{
    using namespace Diligent;

    HWND NativeWindowHandle = window->GetNativeHandle();

    SwapChainDesc SCDesc;
    FullScreenModeDesc fullScreenModeDesc;
    fullScreenModeDesc.Fullscreen = false;

    switch (m_DeviceType)
    {
#ifdef D3D11_SUPPORTED
    case DeviceType::D3D11: {
        EngineD3D11CreateInfo EngineCI;
#if ENGINE_DLL
        GetEngineFactoryD3D11Type GetEngineFactoryD3D11 = nullptr;
        // Load the dll and import GetEngineFactoryD3D11() function
        LoadGraphicsEngineD3D11(GetEngineFactoryD3D11);
#endif
        auto* pFactoryD3D11 = GetEngineFactoryD3D11();
        pFactoryD3D11->CreateDeviceAndContextsD3D11(EngineCI, &m_device, &m_immediateContext);
        pFactoryD3D11->CreateSwapChainD3D11(m_device, m_immediateContext, SCDesc,
                                            fullScreenModeDesc, NativeWindowHandle, &m_swapChain);
    }
    break;
#endif
#ifdef D3D12_SUPPORTED
    case DeviceType::D3D12: {
#if ENGINE_DLL
        GetEngineFactoryD3D12Type GetEngineFactoryD3D12 = nullptr;
        // Load the dll and import GetEngineFactoryD3D12() function
        LoadGraphicsEngineD3D12(GetEngineFactoryD3D12);
#endif
        EngineD3D12CreateInfo EngineCI;
        auto* pFactoryD3D12 = GetEngineFactoryD3D12();
        pFactoryD3D12->CreateDeviceAndContextsD3D12(EngineCI, &m_device, &m_immediateContext);
        pFactoryD3D12->CreateSwapChainD3D12(m_device, m_immediateContext, SCDesc,
                                            fullScreenModeDesc, NativeWindowHandle, &m_swapChain);
    }
    break;
#endif
#ifdef GL_SUPPORTED
    case DeviceType::OpenGL: {

#if ENGINE_DLL
        // Declare function pointer
        GetEngineFactoryOpenGLType GetEngineFactoryOpenGL = nullptr;
        // Load the dll and import GetEngineFactoryOpenGL() function
        LoadGraphicsEngineOpenGL(GetEngineFactoryOpenGL);
#endif
        auto* pFactoryOpenGL = GetEngineFactoryOpenGL();
        EngineGLCreateInfo EngineCI;
        EngineCI.pNativeWndHandle = NativeWindowHandle;
        pFactoryOpenGL->CreateDeviceAndSwapChainGL(EngineCI, &m_device, &m_immediateContext, SCDesc,
                                                   &m_swapChain);
    }
    break;
#endif
#ifdef VULKAN_SUPPORTED
    case DeviceType::Vulkan: {
#if ENGINE_DLL
        GetEngineFactoryVkType GetEngineFactoryVk = nullptr;
        // Load the dll and import GetEngineFactoryVk() function
        LoadGraphicsEngineVk(GetEngineFactoryVk);
#endif
        EngineVkCreateInfo EngineCI;
        auto* pFactoryVk = GetEngineFactoryVk();
        pFactoryVk->CreateDeviceAndContextsVk(EngineCI, &m_device, &m_immediateContext);
        pFactoryVk->CreateSwapChainVk(m_device, m_immediateContext, SCDesc, NativeWindowHandle,
                                      &m_swapChain);
    }
    break;
#endif
    default: {
        RED_ABORT("Unknown device type");
        break;
    }
    }
}

void RenderingEngine::WindowResizeCallBack(uint32_t width, uint32_t height)
{
    if (m_swapChain) m_swapChain->Resize(width, height);
}

} // namespace red
