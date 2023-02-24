#pragma once

#include "RedEngine/Math/Vector.hpp"

namespace red
{

class AABB
{
public:
    inline AABB() = default;
    inline AABB(const Vector2& position, const Vector2& size);
    ~AABB() = default;

    inline AABB& Grow(const Vector2& point);

    inline bool Intersect(const AABB& other);

private:
    Vector2 m_min;
    Vector2 m_max;
};

}  // namespace red

#include "inl/AABB.inl"