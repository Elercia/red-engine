#include "RedEngine/Rendering/Color.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Utils/StringUtils.hpp"

namespace red
{
template <>
String Serialize(const Color& value)
{
    return fmt::format("{};{};{};{}", value.r, value.g, value.b, value.a);
}

template <>
bool Deserialize(Color& value, const String& str)
{
    const char* it = str.data();
    const char* end = (&str.back()) + 1;

    CheckReturn(StringParser::ReadFloat(&it, end, value.r));
    CheckReturn(StringParser::Expect(&it, end, ';'));
    CheckReturn(StringParser::ReadFloat(&it, end, value.g));
    CheckReturn(StringParser::Expect(&it, end, ';'));
    CheckReturn(StringParser::ReadFloat(&it, end, value.b));
    CheckReturn(StringParser::Expect(&it, end, ';'));
    CheckReturn(StringParser::ReadFloat(&it, end, value.a));

    return true;
}
}