#pragma once

#include <string>
#include <vector>
#include <memory>
#include <SDL2/SDL_render.h>

#include "../../Math/Vector.hpp"
#include "Component.hpp"

namespace red
{
class Texture2D;

class Sprite : public Component
{
    RED_COMPONENT("SPRITE")

public:
    Sprite(Entity* entity, std::shared_ptr<Texture2D> texture);

    [[nodiscard]] std::shared_ptr<Texture2D> GetTexture() const;

private:
    std::shared_ptr<Texture2D> m_texture;
};
}  // namespace red
