
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
}

void RenderingEngine::WindowResizeCallBack(uint32_t width, uint32_t height)
{
}

}  // namespace red
