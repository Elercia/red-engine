#include "RedEngine/Rendering/Color.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Utils/StringUtils.hpp"

namespace red
{
template <>
std::string Serialize(const Color& value)
{
    return fmt::format("{};{};{};{}", value.r, value.g, value.b, value.a);
}

template <>
bool Deserialize(Color& value, const std::string& str)
{
    const char* it = str.data();
    const char* end = (&str.back()) + 1;

    CheckReturn(utils::StringParser::ReadFloat(&it, end, value.r));
    CheckReturn(utils::StringParser::Expect(&it, end, ';'));
    CheckReturn(utils::StringParser::ReadFloat(&it, end, value.g));
    CheckReturn(utils::StringParser::Expect(&it, end, ';'));
    CheckReturn(utils::StringParser::ReadFloat(&it, end, value.b));
    CheckReturn(utils::StringParser::Expect(&it, end, ';'));
    CheckReturn(utils::StringParser::ReadFloat(&it, end, value.a));

    return true;
}
}  // namespace red