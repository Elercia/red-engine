#include "RedEngine/Core/Components/Sprite.hpp"

#include <utility>

namespace red
{
Sprite::Sprite(Entity *entity, std::shared_ptr<Texture2D> texture)
    : Component(entity), m_texture(std::move(texture))
{
}

std::shared_ptr<Texture2D> Sprite::GetTexture() const { return m_texture; }
}  // namespace red