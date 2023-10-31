#include "RedEngine/Rendering/Text.hpp"

namespace red
{
Text::Text() : m_geometry(), m_material(), m_dirty(false), m_textStr(), m_font(), m_layerIndex(0), m_fontSize(16)
{
}

Text::~Text()
{
}

void Text::SetText(const std::string_view& str)
{
    m_dirty = true;
    m_textStr = str;
}

void Text::SetFont(std::shared_ptr<Font> font)
{
    m_font = font;
    m_dirty = true;
}

}  // namespace red