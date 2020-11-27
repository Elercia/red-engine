#pragma once

#include <RedEngine/RedEngineBase.hpp>

#include <memory>
#include <string>
#include <RedEngine/Math/Vector.hpp>
#include <RedEngine/Core/Components/Transform.hpp>
#include <RedEngine/Core/SubEngine.hpp>
#include "Color.hpp"

struct SDL_Renderer;

namespace red
{
class Window;
class Sprite;
class CameraComponent;

class RenderingEngine : public SubEngine
{
public:
    RenderingEngine();
    ~RenderingEngine();

    Window& GetWindow();
    SDL_Renderer* GetRenderer();

    void BeginCameraRendering(CameraComponent* cameraComponent);
    void EndCameraRendering();
    void BeginRenderFrame();
    void EndRenderFrame();

    void Render(CameraComponent* camera, Sprite* sprite, const Transform& transform);

    void DrawLine(CameraComponent* camera, const Vector2& first, const Vector2& second,
                  const Color& color = ColorConstant::RED);

    void DrawLines(CameraComponent* camera, const std::vector<Vector2>& points,
                   const Color& color = ColorConstant::RED, bool isFilled = false);

    void DrawCircle(CameraComponent* camera, const Vector2& center, float radius,
                    const Color& color = ColorConstant::RED);

    void DrawPoint(CameraComponent* camera, const Vector2& coord,
                   const Color& color = ColorConstant::RED);

    void Init(const EngineInitDesc& initDesc) override;

private:
    std::unique_ptr<Window> m_window;
    SDL_Renderer* m_renderer;

    void CreateNewWindow();

    void InitRenderer();
};

}  // namespace red
