
#ifdef PLATFORM_WIN32
#ifdef D3D11_SUPPORTED
#include <DiligentCore/Graphics/GraphicsEngineD3D11/interface/EngineFactoryD3D11.h>
#endif // D3D11_SUPPORTED
#ifdef D3D12_SUPPORTED
#include <DiligentCore/Graphics/GraphicsEngineD3D12/interface/EngineFactoryD3D12.h>
#endif // D3D12_SUPPORTED
#endif // PLATFORM_WIN32
#ifdef GL_SUPPORTED
#include <DiligentCore/Graphics/GraphicsEngineOpenGL/interface/EngineFactoryOpenGL.h>
#endif // GL_SUPPORTED
#ifdef VULKAN_SUPPORTED
#include <DiligentCore/Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h>
#endif // VULKAN_SUPPORTED

#include <RedEngine/Window.hpp>
#include <RedEngine/debug/Debug.hpp>
#include <RedEngine/engine/RenderingEngine.hpp>

namespace red
{
RenderingEngine::RenderingEngine() {}
RenderingEngine::~RenderingEngine() {}

void RenderingEngine::InitializeEngine(Window* window)
{
<<<<<<< HEAD
=======
    using namespace Diligent;

#ifdef PLATFORM_WIN32
    HWND windowHandle = window->GetNativeHandle();
#endif

#ifdef PLATFORM_LINUX
    ::Window windowHandle = window->GetNativeHandle();
    Display* display = window->GetNativeDisplay();
#endif

    SwapChainDesc SCDesc;
    FullScreenModeDesc fullScreenModeDesc;
    fullScreenModeDesc.Fullscreen = false;

    switch (m_DeviceType)
    {
#if PLATFORM_WIN32
#ifdef D3D11_SUPPORTED
        case DeviceType::D3D11:
        {
            EngineD3D11CreateInfo EngineCI;
#if ENGINE_DLL
            GetEngineFactoryD3D11Type GetEngineFactoryD3D11 = nullptr;
            // Load the dll and import GetEngineFactoryD3D11() function
            LoadGraphicsEngineD3D11(GetEngineFactoryD3D11);
#endif
            auto* pFactoryD3D11 = GetEngineFactoryD3D11();
            pFactoryD3D11->CreateDeviceAndContextsD3D11(EngineCI, &m_device, &m_immediateContext);
            pFactoryD3D11->CreateSwapChainD3D11(m_device, m_immediateContext, SCDesc,
                                                fullScreenModeDesc, windowHandle, &m_swapChain);
        }
        break;
#endif  // D3D11_SUPPORTED
#ifdef D3D12_SUPPORTED
        case DeviceType::D3D12:
        {
#if ENGINE_DLL
            GetEngineFactoryD3D12Type GetEngineFactoryD3D12 = nullptr;
            // Load the dll and import GetEngineFactoryD3D12() function
            LoadGraphicsEngineD3D12(GetEngineFactoryD3D12);
#endif
            EngineD3D12CreateInfo EngineCI;
            auto* pFactoryD3D12 = GetEngineFactoryD3D12();
            pFactoryD3D12->CreateDeviceAndContextsD3D12(EngineCI, &m_device, &m_immediateContext);
            pFactoryD3D12->CreateSwapChainD3D12(m_device, m_immediateContext, SCDesc,
                                                fullScreenModeDesc, windowHandle, &m_swapChain);
        }
        break;
#endif  // D3D12_SUPPORTED
#endif  // PLATFORM_WIN32
#ifdef GL_SUPPORTED
        case DeviceType::OpenGL:
        {
#if PLATFORM_LINUX
            SwapChainDesc SCDesc;
            Uint32 NumDeferredCtx = 0;
            // Declare function pointer
            auto* pFactoryOpenGL = GetEngineFactoryOpenGL();

            EngineGLCreateInfo CreationAttribs;
            CreationAttribs.pNativeWndHandle = reinterpret_cast<void*>(windowHandle);
            CreationAttribs.pDisplay = display;
            pFactoryOpenGL->CreateDeviceAndSwapChainGL(CreationAttribs, &m_device,
                                                       &m_immediateContext, SCDesc, &m_swapChain);
#endif  // PLATFORM_LINUX
#if PLATFORM_WIN32
#if ENGINE_DLL
            // Declare function pointer
            GetEngineFactoryOpenGLType GetEngineFactoryOpenGL = nullptr;
            // Load the dll and import GetEngineFactoryOpenGL() function
            if(!LoadGraphicsEngineOpenGL(GetEngineFactoryOpenGL))
            {
                RED_ERROR("Cannot load LoadGraphicsEngineOpenGL")
            }
#endif
            auto* pFactoryOpenGL = GetEngineFactoryOpenGL();
            EngineGLCreateInfo EngineCI;
            EngineCI.pNativeWndHandle = windowHandle;
            pFactoryOpenGL->CreateDeviceAndSwapChainGL(EngineCI, &m_device, &m_immediateContext,
                                                       SCDesc, &m_swapChain);
#endif  // PLATFORM_WIN32
        }
        break;
#endif  // GL_SUPPORTED
#ifdef VULKAN_SUPPORTED
        case DeviceType::Vulkan:
        {
#if PLATFORM_LINUX
            //            EngineVkCreateInfo EngVkAttribs;
            //
            //            auto* pFactoryVk = GetEngineFactoryVk();
            //            pFactoryVk->CreateDeviceAndContextsVk(EngVkAttribs, &m_device,
            //            &m_immediateContext); SwapChainDesc SCDesc; LinuxNativeWindow XCBWindow;
            //            XCBWindow.WindowId = xcbInfo.window;
            //            XCBWindow.pXCBConnection = xcbInfo.connection;
            //
            //            pFactoryVk->CreateSwapChainVk(m_device, m_immediateContext, SCDesc,
            //            XCBWindow,
            //                                          &m_swapChain);
            RED_ERROR("Unsuported")
#endif
#if PLATFORM_WIN32
#if ENGINE_DLL
            GetEngineFactoryVkType GetEngineFactoryVk = nullptr;
            // Load the dll and import GetEngineFactoryVk() function
            LoadGraphicsEngineVk(GetEngineFactoryVk);
#endif
            EngineVkCreateInfo EngineCI;
            auto* pFactoryVk = GetEngineFactoryVk();
            pFactoryVk->CreateDeviceAndContextsVk(EngineCI, &m_device, &m_immediateContext);
            pFactoryVk->CreateSwapChainVk(m_device, m_immediateContext, SCDesc, windowHandle,
                                          &m_swapChain);
#endif
        }
        break;
#endif
        default:
        {
            RED_ABORT("Unknown device type");
            break;
        }
    }
>>>>>>> refactor_cmake_branch
}

void RenderingEngine::WindowResizeCallBack(uint32_t width, uint32_t height)
{
}

}  // namespace red
