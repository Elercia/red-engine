#pragma once

#include <memory>
#include <string>
#include <RedEngine/Core/SubEngine.hpp>

struct SDL_Renderer;

namespace red
{
class Window;
class Sprite;

class RenderingEngine : public SubEngine
{
public:
    RenderingEngine();
    ~RenderingEngine();

    Window& GetWindow();
    SDL_Renderer* GetRenderer();

    void BeginRenderFrame();
    void EndRenderFrame();

    void DebugDrawRect();
    void Render(Sprite* sprite);

private:
    std::unique_ptr<Window> m_window;
    SDL_Renderer* m_renderer;

    void CreateNewWindow();

    void InitRenderer();
};

}  // namespace red
