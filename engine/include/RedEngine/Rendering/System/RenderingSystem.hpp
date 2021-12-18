#pragma once

#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Rendering/Renderer.hpp"

namespace red
{
class CameraComponent;

class RenderingSystem : public System
{
public:
    explicit RenderingSystem(World* world);

    virtual void Init() override;

    void Update() override;

	virtual void BeginRender() override;
	virtual void Render() override;
	virtual void EndRender() override;

    Renderer* GetRenderer();

private:
    void DrawDebug(CameraComponent* camera);

private:
    Renderer* m_renderer;
};

}  // namespace red
