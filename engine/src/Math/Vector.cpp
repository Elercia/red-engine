#include "RedEngine/Math/Vector.hpp"

#include "RedEngine/Math/MathModule.hpp"

namespace red
{
constexpr float s_physicDistanceFactor = 0.01f;

b2Vec2 ConvertToPhysicsVector(const Vector2& vector2)
{
    return b2Vec2(vector2.x * s_physicDistanceFactor, vector2.y * s_physicDistanceFactor);
}

Vector2 ConvertFromPhysicsVector(const b2Vec2& vector2)
{
    return Vector2(vector2.x, vector2.y) * (1.f / s_physicDistanceFactor);
}
}  // namespace red