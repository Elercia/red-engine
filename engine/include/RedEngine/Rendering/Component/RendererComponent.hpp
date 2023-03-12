#pragma once

#include "RedEngine/Core/Entity/Components/Component.hpp"

namespace red
{
class Renderer;

class RendererComponent : public Component
{
public:
    RendererComponent(Entity* entity);
    ~RendererComponent();

    Renderer& GetRenderer();

private:
    Renderer* m_renderer;
};
}  // namespace red
