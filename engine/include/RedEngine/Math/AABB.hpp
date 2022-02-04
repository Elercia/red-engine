#pragma once

#include "RedEngine/Math/Vector.hpp"

namespace red
{

class AABB
{
public:
    inline AABB();
    ~AABB() = default;

    inline AABB& Grow(const Vector3& /*point*/);

    inline bool Intersect(const AABB& /*other*/);

private:
    Vector2 m_center;
    Vector2 m_min;
    Vector2 m_max;
};

}  // namespace red

#include "inl/AABB.inl"