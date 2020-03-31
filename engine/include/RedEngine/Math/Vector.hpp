#pragma once

namespace red
{
class Vector3
{
public:
    Vector3() : Vector3(0, 0, 0) {}
    Vector3(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {}
    ~Vector3() = default;

    float m_x, m_y, m_z;
};

}  // namespace red