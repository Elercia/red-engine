#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Container/Map.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Resources/Resource.hpp"

namespace red
{
class Texture2D;

using GlyphCode = uint32;

struct Glyph
{
    Vector4 atlasBounds;
    Vector4 planeBounds;
    float advance;
};

using GlyphMap = Map<GlyphCode, Glyph>;

// MSDF Fonts
class Font : public IResource
{
    friend class FontResourceLoader;
    friend class Renderer;

public:
    RED_RESOURCE(ResourceType::FONT, L"font");

    Font(const Path& resourceId);
    ~Font();

private:
    std::shared_ptr<Texture2D> m_atlas;
    GlyphMap m_glyphs;

    int m_pixelRange;
    int size;
};
}  // namespace red
