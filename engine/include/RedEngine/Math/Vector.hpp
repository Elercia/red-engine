#pragma once

namespace red
{
class Vector3
{
public:
    Vector3() : Vector3(0, 0, 0) {}
    Vector3(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {}

    Vector3(const Vector3&) = default;
    Vector3(Vector3&&) = default;

    Vector3& operator=(const Vector3&) = default;
    Vector3& operator=(Vector3&&) = default;

    ~Vector3() = default;

    float m_x, m_y, m_z;
};

class Vector2
{
public:
    Vector2() : Vector2(0, 0) {}
    Vector2(int x, int y) : m_x(x), m_y(y) {}

    Vector2(const Vector2&) = default;
    Vector2(Vector2&&) = default;

    Vector2& operator=(const Vector2&) = default;
    Vector2& operator=(Vector2&&) = default;

    ~Vector2() = default;

    int m_x, m_y;
};

}  // namespace red