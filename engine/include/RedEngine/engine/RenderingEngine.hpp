#pragma once

#include <iomanip>
#include <iostream>
#include <memory>

#include <DiligentCore/Graphics/GraphicsEngineD3D11/interface/EngineFactoryD3D11.h>
#include <DiligentCore/Graphics/GraphicsEngineD3D12/interface/EngineFactoryD3D12.h>
#include <DiligentCore/Graphics/GraphicsEngineOpenGL/interface/EngineFactoryOpenGL.h>
#include <DiligentCore/Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h>

#include <DiligentCore/Graphics/GraphicsEngine/interface/DeviceContext.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/RenderDevice.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/SwapChain.h>

#include <DiligentCore/Common/interface/RefCntAutoPtr.h>

namespace red
{
class Window;

class RenderingEngine
{
public:
    RenderingEngine();
    ~RenderingEngine();

    void InitializeEngine(Window* window);

    void WindowResizeCallBack(uint32_t width, uint32_t height);

    Diligent::DeviceType GetDeviceType() const { return m_DeviceType; }

private:
    Diligent::RefCntAutoPtr<Diligent::IRenderDevice> m_device;
    Diligent::RefCntAutoPtr<Diligent::IDeviceContext> m_immediateContext;
    Diligent::RefCntAutoPtr<Diligent::ISwapChain> m_swapChain;
    Diligent::RefCntAutoPtr<Diligent::IPipelineState> m_pso;
    Diligent::DeviceType m_DeviceType = Diligent::DeviceType::OpenGL;
};

} // namespace red
