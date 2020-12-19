#pragma once

#include <RedEngine/RedEngineBase.hpp>

#include <RedEngine/Resources/Resource.hpp>
#include <RedEngine/Math/Vector.hpp>

#include <SDL2/SDL_render.h>

#include <string>

namespace red
{
class Texture2D : public IResource
{
    friend class ResourceEngine;
    friend class RenderingEngine;

public:
    explicit Texture2D(ResourceId resourceId);
    ~Texture2D() override = default;

    [[nodiscard]] Vector2i GetTextureSize() const;
    void ChangeTextureSize(const Vector2i& newSize);

    static ResourceId GetResourceIdFromPath(const std::string& resourceId);

    void Release() override;

private:
    SDL_Texture* m_sdlTexture{nullptr};
    SDL_Rect m_textureSize{0, 0, 0, 0};
};
}  // namespace red
