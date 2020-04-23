#pragma once

#include <RedEngine/Resources/Resource.hpp>

#include <SDL2/SDL_render.h>

namespace red
{
class Texture : public Resource
{
    friend class ResourceEngine;
    friend class RenderingEngine;

public:
    explicit Texture(ResourceId resourceId);
    ~Texture() override;

    [[nodiscard]] SDL_Rect GetTextureSize() const;

    static ResourceId GetNextResourceId();

private:
    static ResourceId s_nextResourceId;

    SDL_Texture* m_sdlTexture{nullptr};
    SDL_Rect m_textureSize{0, 0, 0, 0};
};
}  // namespace red
