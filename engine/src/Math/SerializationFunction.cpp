#include "RedEngine/Math/SerializationFunction.hpp"

namespace red
{
std::string Serialize(const Vector2& value)
{
    return std::to_string(value.x) + ";" + std::to_string(value.y);
}

bool Deserialize(Vector2& /*value*/, const std::string& /*str*/)
{
    return false;
}
}  // namespace red