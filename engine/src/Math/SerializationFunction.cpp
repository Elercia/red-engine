#include "RedEngine/Math/MathModule.hpp"
#include "RedEngine/Math/SerializationFunction.hpp"

namespace red
{
template <>
std::string Serialize(const Vector2& value)
{
    return std::to_string(value.x) + ";" + std::to_string(value.y);
}

template <>
bool Deserialize(Vector2& /*value*/, const std::string& /*str*/)
{
    return false;
}
}  // namespace red