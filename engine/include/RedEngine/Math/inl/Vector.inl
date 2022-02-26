#include "RedEngine/Utils/Types.hpp"

namespace red
{
template <typename T>
constexpr Vector2T<T> operator+(const Vector2T<T>& l, const Vector2T<T>& r)
{
    Vector2T<T> value;

    value.x = l.x + r.x;
    value.y = l.y + r.y;

    return value;
}

template <typename T>
constexpr Vector2T<T> operator-(const Vector2T<T>& l, const Vector2T<T>& r)
{
    Vector2T<T> value;

    value.x = l.x - r.x;
    value.y = l.y - r.y;

    return value;
}

template <typename T>
constexpr Vector2T<T> operator*(const Vector2T<T>& l, const Vector2T<T>& r)
{
    Vector2T<T> value;

    value.x = l.x * r.x;
    value.y = l.y * r.y;

    return value;
}

template <typename T>
constexpr Vector2T<T> operator*(const Vector2T<T>& l, T scalar)
{
    Vector2T<T> value;

    value.x = l.x * scalar;
    value.y = l.y * scalar;

    return value;
}

template <typename T>
constexpr Vector2T<T> operator-(const Vector2T<T>& l)
{
    Vector2T<T> value;

    value.x = -l.x;
    value.y = -l.y;

    return value;
}

template <typename T>
constexpr Vector3T<T> operator-(const Vector3T<T>& l)
{
    Vector3T<T> value;

    value.x = -l.x;
    value.y = -l.y;
    value.z = -l.z;

    return value;
}

template <typename T>
constexpr Vector4T<T> operator-(const Vector4T<T>& l)
{
    Vector4T<T> value;

    value.x = -l.x;
    value.y = -l.y;
    value.z = -l.z;
    value.w = -l.w;

    return value;
}

template <typename T>
constexpr Vector2T<T> operator+(const Vector2T<T>& l)
{
    Vector2T<T> value = l;
    return value;
}

template <typename T>
constexpr Vector3T<T> operator+(const Vector3T<T>& l)
{
    Vector3T<T> value = l;
    return value;
}

template <typename T>
constexpr Vector4T<T> operator+(const Vector4T<T>& l)
{
    Vector4T<T> value = l;
    return value;
}

template <typename T>
constexpr T& Vector4T<T>::operator[](uint8 i)
{
    return (&x)[i];
}

template <typename T>
constexpr const T& Vector4T<T>::operator[](uint8 i) const
{
    return (&x)[i];
}

}  // namespace red