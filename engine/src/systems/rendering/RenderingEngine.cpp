#include <RedEngine/systems/rendering/RenderingEngine.hpp>

namespace red
{
void RenderingEngine::InitializeEngine(HWND NativeWindowHandle)
{
    using namespace Diligent;

    SwapChainDesc SCDesc;
    FullScreenModeDesc fullScreenModeDesc;
    fullScreenModeDesc.Fullscreen = false;

    switch (m_DeviceType)
    {
    case DeviceType::D3D11: {
        EngineD3D11CreateInfo EngineCI;
#if ENGINE_DLL
        GetEngineFactoryD3D11Type GetEngineFactoryD3D11 = nullptr;
        // Load the dll and import GetEngineFactoryD3D11() function
        LoadGraphicsEngineD3D11(GetEngineFactoryD3D11);
#endif
        auto* pFactoryD3D11 = GetEngineFactoryD3D11();
        pFactoryD3D11->CreateDeviceAndContextsD3D11(EngineCI, &m_pDevice, &m_pImmediateContext);
        pFactoryD3D11->CreateSwapChainD3D11(m_pDevice, m_pImmediateContext, SCDesc,
                                            fullScreenModeDesc, NativeWindowHandle, &m_pSwapChain);
    }
    break;

    case DeviceType::D3D12: {
#if ENGINE_DLL
        GetEngineFactoryD3D12Type GetEngineFactoryD3D12 = nullptr;
        // Load the dll and import GetEngineFactoryD3D12() function
        LoadGraphicsEngineD3D12(GetEngineFactoryD3D12);
#endif
        EngineD3D12CreateInfo EngineCI;
        auto* pFactoryD3D12 = GetEngineFactoryD3D12();
        pFactoryD3D12->CreateDeviceAndContextsD3D12(EngineCI, &m_pDevice, &m_pImmediateContext);
        pFactoryD3D12->CreateSwapChainD3D12(m_pDevice, m_pImmediateContext, SCDesc,
                                            fullScreenModeDesc, NativeWindowHandle, &m_pSwapChain);
    }
    break;

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
        pFactoryOpenGL->CreateDeviceAndSwapChainGL(EngineCI, &m_pDevice, &m_pImmediateContext,
                                                   SCDesc, &m_pSwapChain);
    }
    break;

    case DeviceType::Vulkan: {
#if ENGINE_DLL
        GetEngineFactoryVkType GetEngineFactoryVk = nullptr;
        // Load the dll and import GetEngineFactoryVk() function
        LoadGraphicsEngineVk(GetEngineFactoryVk);
#endif
        EngineVkCreateInfo EngineCI;
        auto* pFactoryVk = GetEngineFactoryVk();
        pFactoryVk->CreateDeviceAndContextsVk(EngineCI, &m_pDevice, &m_pImmediateContext);
        pFactoryVk->CreateSwapChainVk(m_pDevice, m_pImmediateContext, SCDesc, NativeWindowHandle,
                                      &m_pSwapChain);
    }
    break;

    default:
        std::cerr << "Unknown device type";
    }
}
} // namespace red
