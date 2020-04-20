#pragma once

#include <string>
#include <vector>
#include <SDL2/SDL_render.h>

#include "../../Math/Vector.hpp"
#include "../../Core/Components/Component.hpp"

namespace red
{
struct LoadState
{
    enum Enum
    {
        STATE_NOT_LOADED,
        STATE_LOADED,
        STATE_ERROR
    };
};

class Sprite : public Component
{
    RED_COMPONENT("SPRITE")

    friend class ResourceEngine;
    friend class RenderingEngine;

public:
    Sprite(Entity* entity, std::string path);

    std::string GetPath() { return m_path; };

    LoadState::Enum GetLoadedState() { return m_isLoaded; }

private:
    LoadState::Enum m_isLoaded;
    std::string m_path;

    SDL_Texture* m_texture;
    SDL_Rect m_sdlPos{0, 0, 0, 0};
    SDL_Rect m_sdlSize{0, 0, 0, 0};
};
}  // namespace red
