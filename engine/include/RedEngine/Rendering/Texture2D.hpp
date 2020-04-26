#pragma once

#include <RedEngine/Resources/Resource.hpp>

#include <SDL2/SDL_render.h>

namespace red
{
class Texture2D : public Resource
{
    friend class ResourceEngine;
    friend class RenderingEngine;

public:
    explicit Texture2D(ResourceId_t resourceId);
    ~Texture2D() override;

    [[nodiscard]] SDL_Rect GetTextureSize() const;

    static ResourceId_t GetNextResourceId();

private:
    static ResourceId_t s_nextResourceId;

    SDL_Texture* m_sdlTexture{nullptr};
    SDL_Rect m_textureSize{0, 0, 0, 0};
};
}  // namespace red
