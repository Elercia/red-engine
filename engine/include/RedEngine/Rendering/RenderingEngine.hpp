#pragma once

#include <memory>
#include <string>

namespace red
{
class Window;

class RenderingEngine
{
public:
    RenderingEngine();
    ~RenderingEngine();

    Window& GetWindow();

private:
    std::unique_ptr<Window> m_window;

    void CreateNewWindow(std::string title);
};

}  // namespace red
