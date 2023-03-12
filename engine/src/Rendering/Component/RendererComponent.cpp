#include "RedEngine/Rendering/Component/RendererComponent.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Rendering/Renderer.hpp"

namespace red
{
RendererComponent::RendererComponent(Entity* entity) : Component(entity)
{
    m_renderer = new Renderer();
}

RendererComponent::~RendererComponent()
{
    RED_SAFE_DELETE(m_renderer);
}

Renderer& red::RendererComponent::GetRenderer()
{
    return *m_renderer;
}
}  // namespace red
