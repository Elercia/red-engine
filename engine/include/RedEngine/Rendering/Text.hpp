#pragma once

#include "RedEngine/Rendering/Component/Renderable.hpp"
#include "RedEngine/Rendering/Resource/Font.hpp"
#include "RedEngine/Rendering/Resource/Geometry.hpp"

#include <string>

namespace red
{
class Text
{
    friend class Renderer;

public:
    Text();
    ~Text();

    void SetText(const std::string_view& str);
    void SetFont(std::shared_ptr<Font> font);

private:
    // Filled by the renderer
    Geometry m_geometry;
    MaterialInstance m_material;
    bool m_dirty;

    // User text, font, layer, etc
    std::string m_textStr;
    std::shared_ptr<Font> m_font;
    RenderLayerIndex m_layerIndex;

    float m_fontSize;
};
}  // namespace red