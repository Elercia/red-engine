#pragma once

#include <RedEngine/Resources/Resource.hpp>
#include <RedEngine/Math/Point.hpp>

#include <SDL2/SDL_render.h>

namespace red
{
class Texture2D : public Resource
{
    friend class ResourceEngine;
    friend class RenderingEngine;

public:
    explicit Texture2D(ResourceId_t resourceId);
    ~Texture2D() override = default;

    [[nodiscard]] Point GetTextureSize() const;
    void ChangeTextureSize(const Point& newSize);

    static ResourceId_t GetNextResourceId();

    void Release() override;

private:
    static ResourceId_t s_nextResourceId;

    SDL_Texture* m_sdlTexture{nullptr};
    SDL_Rect m_textureSize{0, 0, 0, 0};
};
}  // namespace red
