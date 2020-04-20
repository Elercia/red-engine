#include "RedEngine/Rendering/Components/Sprite.hpp"

#include <utility>

namespace red
{
Sprite::Sprite(Entity* entity, std::string path)
    : Component(entity)
    , m_isLoaded(LoadState::STATE_NOT_LOADED)
    , m_path(std::move(path))
    , m_texture(nullptr)
{
}
}  // namespace red