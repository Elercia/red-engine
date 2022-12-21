#pragma once

#include <box2d/b2_math.h>

namespace red
{
template <typename T>
class Vector2T;
template <typename T>
class Vector3T;
template <typename T>
class Vector4T;

template <typename T>
class Vector2T
{
public:
    constexpr Vector2T() : Vector2T(T(), T())
    {
    }

    constexpr Vector2T(T px, T py) : x(px), y(py)
    {
    }

    constexpr Vector2T(const Vector2T<T>&) = default;
    constexpr Vector2T(Vector2T<T>&&) = default;

    ~Vector2T() = default;

    constexpr Vector2T<T>& operator=(const Vector2T<T>&) = default;
    constexpr Vector2T<T>& operator=(Vector2T<T>&&) = default;

    constexpr T& operator[](uint8 i);
    constexpr const T& operator[](uint8 i) const;

    constexpr T LengthSquare() const;
    constexpr T Length() const;

    constexpr Vector2T<T> Normalize() const;

    union
    {
        T x;
        T width;
    };

    union
    {
        T y;
        T height;
    };
};

template <typename T>
class Vector3T
{
public:
    constexpr Vector3T() : Vector3T(T(), T(), T())
    {
    }

    constexpr Vector3T(T xx, T yy, T zz) : x(xx), y(yy), z(zz)
    {
    }

    constexpr Vector3T(const Vector2T<T>& o, T z) : x(o.x), y(o.y), z(z)
    {
    }

    ~Vector3T() = default;

    constexpr Vector3T(const Vector3T&) = default;
    constexpr Vector3T(Vector3T&&) = default;

    constexpr Vector3T<T>& operator=(const Vector3T<T>&) = default;
    constexpr Vector3T<T>& operator=(Vector3T<T>&&) = default;

    constexpr T& operator[](uint8 i);
    constexpr const T& operator[](uint8 i) const;

    constexpr T LengthSquare() const;
    constexpr T Length() const;

    constexpr Vector3T<T> Normalize() const;

    T x, y, z;
};

template <typename T>
class Vector4T
{
public:
    constexpr Vector4T() : Vector4T(T(), T(), T(), T())
    {
    }

    constexpr Vector4T(T px, T py, T pz, T pw) : x(px), y(py), z(pz), w(pw)
    {
    }

    ~Vector4T() = default;

    constexpr Vector4T(const Vector4T<T>&) = default;
    constexpr Vector4T(Vector4T<T>&&) = default;

    constexpr Vector4T<T>& operator=(const Vector4T<T>&) = default;
    constexpr Vector4T<T>& operator=(Vector4T&&) = default;

    constexpr T& operator[](uint8 i);
    constexpr const T& operator[](uint8 i) const;

    constexpr T LengthSquare() const;
    constexpr T Length() const;

    constexpr Vector4T<T> Normalize() const;

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

using Vector3 = Vector3T<float>;
using Vector3i = Vector3T<int>;

using Vector4 = Vector4T<float>;
using Vector4i = Vector4T<int>;

template <typename T>
constexpr Vector2T<T> operator+(const Vector2T<T>& l, const Vector2T<T>& r);
template <typename T>
constexpr Vector2T<T> operator-(const Vector2T<T>& l, const Vector2T<T>& r);
template <typename T>
constexpr Vector2T<T> operator*(const Vector2T<T>& l, const Vector2T<T>& r);
template <typename T>
constexpr Vector2T<T> operator*(const Vector2T<T>& l, T scalar);
template <typename T>
constexpr Vector2T<T> operator/(const Vector2T<T>& l, T scalar);

template <typename T>
constexpr Vector3T<T> operator+(const Vector3T<T>& l, const Vector3T<T>& r);
template <typename T>
constexpr Vector3T<T> operator-(const Vector3T<T>& l, const Vector3T<T>& r);
template <typename T>
constexpr Vector3T<T> operator*(const Vector3T<T>& l, const Vector3T<T>& r);
template <typename T>
constexpr Vector3T<T> operator*(const Vector3T<T>& l, T scalar);
template <typename T>
constexpr Vector3T<T> operator/(const Vector3T<T>& l, T scalar);

template <typename T>
constexpr Vector2T<T> operator-(const Vector2T<T>& l);
template <typename T>
constexpr Vector2T<T> operator+(const Vector2T<T>& l);

template <typename T>
constexpr Vector3T<T> operator-(const Vector3T<T>& l);
template <typename T>
constexpr Vector3T<T> operator+(const Vector3T<T>& l);

template <typename T>
constexpr Vector4T<T> operator-(const Vector4T<T>& l);
template <typename T>
constexpr Vector4T<T> operator+(const Vector4T<T>& l);

template <typename T>
constexpr Vector3T<T> Cross(const Vector3T<T>& a, const Vector3T<T>& b);

template <typename T>
constexpr T Dot(const Vector2T<T>& a, const Vector2T<T>& b);
template <typename T>
constexpr T Dot(const Vector3T<T>& a, const Vector3T<T>& b);

}  // namespace red

#include "inl/Vector.inl"