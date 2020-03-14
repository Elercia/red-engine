#pragma once

#include <iomanip>
#include <iostream>
#include <memory>

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

private:
};

}  // namespace red
