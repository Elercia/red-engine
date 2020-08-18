#pragma once

#include <Box2D/Common/b2Math.h>

namespace red
{
template <typename T>
class Vector2T
{
public:
    Vector2T() : Vector2T(T(), T()) {}
    Vector2T(T px, T py) : x(px), y(py) {}

    Vector2T(const Vector2T<T>&) = default;
    Vector2T(Vector2T<T>&&) = default;

    ~Vector2T() = default;

    Vector2T<T>& operator=(const Vector2T<T>&) = default;
    Vector2T<T>& operator=(Vector2T<T>&&) = default;

    Vector2T<T> operator+(const Vector2T<T>& other) const;
    Vector2T<T> operator*(T scalar) const;

    operator b2Vec2() const;

    T x, y;
};

template <typename T>
class Vector3T
{
public:
    Vector3T() : Vector3T(T(), T(), T()) {}
    Vector3T(T x, T y, T z) : m_x(x), m_y(y), m_z(z) {}

    Vector3T(const Vector3T&) = default;
    Vector3T(Vector3T&&) = default;

    Vector3T<T>& operator=(const Vector3T<T>&) = default;
    Vector3T<T>& operator=(Vector3T<T>&&) = default;

    ~Vector3T() = default;

    T m_x, m_y, m_z;
};

template <typename T>
class Vector4T
{
public:
    Vector4T() : Vector4T(T(), T(), T(), T()) {}
    Vector4T(T px, T py, T pz, T pw) : x(px), y(py), z(pz), w(pw) {}

    Vector4T(const Vector4T<T>&) = default;
    Vector4T(Vector4T<T>&&) = default;

    Vector4T<T>& operator=(const Vector4T<T>&) = default;
    Vector4T<T>& operator=(Vector4T&&) = default;

    ~Vector4T() = default;

    T x;
    T y;

    union
    {
        T z;
        T width;
    };

    union
    {
        T w;
        T height;
    };
};

using Vector2 = Vector2T<float>;
using Vector2i = Vector2T<int>;

using Vector4 = Vector4T<float>;
using Vector4i = Vector4T<int>;
}  // namespace red

#include "inl/Vector.inl"