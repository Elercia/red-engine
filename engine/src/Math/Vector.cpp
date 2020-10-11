#include <RedEngine/Math/Vector.hpp>

#include "RedEngine/Core/EngineConfig.hpp"

namespace red
{
b2Vec2 ConvertToPhysicsVector(const Vector2& vector2)
{
    return b2Vec2(vector2.x * PHYSICS_PIXEL_PER_METER, vector2.y * PHYSICS_PIXEL_PER_METER);
}

Vector2 ConvertFromPhysicsVector(const b2Vec2& vector2)
{
    return Vector2(vector2.x / PHYSICS_PIXEL_PER_METER, vector2.y / PHYSICS_PIXEL_PER_METER);
}
}  // namespace red