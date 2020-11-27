#include <RedEngine/Math/Vector.hpp>

namespace red
{
b2Vec2 ConvertToPhysicsVector(const Vector2& vector2)
{
    return b2Vec2(vector2.x, vector2.y);
}

Vector2 ConvertFromPhysicsVector(const b2Vec2& vector2)
{
    return Vector2(vector2.x, vector2.y);
}
}  // namespace red