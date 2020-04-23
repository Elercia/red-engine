#pragma once

#include <string>
#include <vector>
#include <SDL2/SDL_render.h>

#include "../../Math/Vector.hpp"
#include "Component.hpp"

namespace red
{
class Texture;

class Sprite : public Component
{
    RED_COMPONENT("SPRITE")

public:
    Sprite(Entity* entity, Texture* texture);

    [[nodiscard]] Texture* GetTexture() const;

private:
    Texture* m_texture;
};
}  // namespace red
