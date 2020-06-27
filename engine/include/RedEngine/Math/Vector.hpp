#pragma once

namespace red
{
class Vector2
{
public:
    Vector2() : Vector2(0.F, 0.F) {}
    Vector2(float px, float py) : x(px), y(py) {}

    Vector2(const Vector2&) = default;
    Vector2(Vector2&&) = default;

    ~Vector2() = default;

    Vector2& operator=(const Vector2&) = default;
    Vector2& operator=(Vector2&&) = default;

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator*(float scalar) const;

    float x, y;
};

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

class Vector4
{
public:
    Vector4() : Vector4(0.F, 0.F, 0.F, 0.F) {}
    Vector4(float px, float py, float pz, float pw) : x(px), y(py), z(pz), w(pw) {}

    Vector4(const Vector4&) = default;
    Vector4(Vector4&&) = default;

    Vector4& operator=(const Vector4&) = default;
    Vector4& operator=(Vector4&&) = default;

    ~Vector4() = default;

    float x;
    float y;

    union
    {
        float z;
        float width;
    };

    union
    {
        float w;
        float height;
    };
};

}  // namespace red