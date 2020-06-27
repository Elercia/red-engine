
#include <RedEngine/Math/Vector.hpp>

namespace red
{
Vector2 Vector2::operator+(const Vector2& other) const
{
    Vector2 value;
    value.x = x + other.x;
    value.y = y + other.y;

    return value;
}

Vector2 Vector2::operator*(float scalar) const
{
    Vector2 value;
    value.x = x * scalar;
    value.y = y * scalar;

    return value;
}

}  // namespace red