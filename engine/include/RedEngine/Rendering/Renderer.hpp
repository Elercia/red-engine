#pragma once

#include "Color.hpp"

#include "RedEngine/Core/Components/Transform.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"

#include <memory>
#include <string>
#include <vector>

struct SDL_Renderer;

namespace red
{
class WindowComponent;
class Sprite;
class CameraComponent;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void BeginCameraRendering(CameraComponent* cameraComponent);
    void EndCameraRendering();
    void BeginRenderFrame();
    void EndRenderFrame();

    void Render(CameraComponent* camera, Sprite* sprite, const Transform& transform);

    void DrawLine(CameraComponent* camera, const Vector2& first, const Vector2& second,
                  const Color& color = ColorConstant::RED);

    void DrawLines(CameraComponent* camera, const std::vector<Vector2>& points, const Color& color = ColorConstant::RED,
                   bool isFilled = false);

    void DrawCircle(CameraComponent* camera, const Vector2& center, float radius,
                    const Color& color = ColorConstant::RED);

    void DrawPoint(CameraComponent* camera, const Vector2& coord, const Color& color = ColorConstant::RED);

    void InitRenderer(WindowComponent* window);
    SDL_Renderer* GetSDLRenderer();

private:
    SDL_Renderer* m_renderer;
};

}  // namespace red
