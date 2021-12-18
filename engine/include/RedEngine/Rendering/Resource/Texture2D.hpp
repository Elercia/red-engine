#pragma once

#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Resources/Resource.hpp"

#include <SDL2/SDL_render.h>
#include <string>

namespace red
{
class Texture2D : public IResource
{
    friend class TextureResourceLoader;
    friend class Renderer;

public:
    RED_RESOURCE(ResourceType::TEXTURE2D);

    explicit Texture2D(const Path& resourceId);
    ~Texture2D() override = default;

    [[nodiscard]] Vector2i GetTextureSize() const;

private:
    uint32 m_textureHandle;
    Vector2i m_size;
};
}  // namespace red
