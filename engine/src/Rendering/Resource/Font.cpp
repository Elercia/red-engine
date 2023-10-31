#include "RedEngine/Rendering/Resource/Font.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Resources/Resource.hpp"

namespace red
{
Font::Font(const Path& resourceId) : IResource(resourceId, ResourceType::FONT)
{
}

Font::~Font()
{
}
}  // namespace red
