#pragma once

#include <iomanip>
#include <iostream>
#include <memory>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

#include "Graphics/GraphicsEngineD3D11/interface/EngineFactoryD3D11.h"
#include "Graphics/GraphicsEngineD3D12/interface/EngineFactoryD3D12.h"
#include "Graphics/GraphicsEngineOpenGL/interface/EngineFactoryOpenGL.h"
#include "Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h"

#include "Graphics/GraphicsEngine/interface/DeviceContext.h"
#include "Graphics/GraphicsEngine/interface/RenderDevice.h"
#include "Graphics/GraphicsEngine/interface/SwapChain.h"

#include "Common/interface/RefCntAutoPtr.h"

namespace red
{
class RenderingEngine
{
public:
    RenderingEngine();
    ~RenderingEngine();

    void InitializeEngine(HWND NativeWindowHandle);

    Diligent::DeviceType GetDeviceType() const { return m_DeviceType; }

private:
    Diligent::RefCntAutoPtr<Diligent::IRenderDevice> m_pDevice;
    Diligent::RefCntAutoPtr<Diligent::IDeviceContext> m_pImmediateContext;
    Diligent::RefCntAutoPtr<Diligent::ISwapChain> m_pSwapChain;
    Diligent::RefCntAutoPtr<Diligent::IPipelineState> m_pPSO;
    Diligent::DeviceType m_DeviceType = Diligent::DeviceType::OpenGL;
};

} // namespace red
