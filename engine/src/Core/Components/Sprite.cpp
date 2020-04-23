#include "RedEngine/Core/Components/Sprite.hpp"

#include <utility>

namespace red
{
Sprite::Sprite(Entity *entity, Texture *texture) : Component(entity), m_texture(texture) {}

Texture *Sprite::GetTexture() const { return m_texture; }
}  // namespace red