#include "RedEngine/Math/Math.hpp"
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
constexpr Vector2T<T> operator/(const Vector2T<T>& l, T scalar)
{
    Vector2T<T> value;

    value.x = l.x / scalar;
    value.y = l.y / scalar;

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
constexpr Vector3T<T> operator+(const Vector3T<T>& l, const Vector3T<T>& r)
{
    Vector3T<T> ret;

    ret.x = l.x + r.x;
    ret.y = l.y + r.y;
    ret.z = l.z + r.z;

    return ret;
}

template <typename T>
constexpr Vector3T<T> operator-(const Vector3T<T>& l, const Vector3T<T>& r)
{
    Vector3T<T> ret;

    ret.x = l.x - r.x;
    ret.y = l.y - r.y;
    ret.z = l.z - r.z;

    return ret;
}

template <typename T>
constexpr Vector3T<T> operator*(const Vector3T<T>& l, const Vector3T<T>& r)
{
    Vector3T<T> ret;

    ret.x = l.x * r.x;
    ret.y = l.y * r.y;
    ret.z = l.z * r.z;

    return ret;
}

template <typename T>
constexpr Vector3T<T> operator*(const Vector3T<T>& l, T scalar)
{
    Vector3T<T> ret;

    ret.x = l.x * scalar;
    ret.y = l.y * scalar;
    ret.z = l.z * scalar;

    return ret;
}

template <typename T>
constexpr Vector3T<T> operator/(const Vector3T<T>& l, T scalar)
{
    Vector3T<T> ret;

    ret.x = l.x / scalar;
    ret.y = l.y / scalar;
    ret.z = l.z / scalar;

    return ret;
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
constexpr T& Vector2T<T>::operator[](uint8 i)
{
    return (&x)[i];
}

template <typename T>
constexpr const T& Vector2T<T>::operator[](uint8 i) const
{
    return (&x)[i];
}

template <typename T>
constexpr T& Vector3T<T>::operator[](uint8 i)
{
    return (&x)[i];
}

template <typename T>
constexpr const T& Vector3T<T>::operator[](uint8 i) const
{
    return (&x)[i];
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

template <typename T>
constexpr T Vector2T<T>::LengthSquare() const
{
    return x * x + y * y;
}

template <typename T>
constexpr T Vector2T<T>::Length() const
{
    return Math::Sqrt(LengthSquare());
}

template <typename T>
constexpr Vector2T<T> Vector2T<T>::Normalize() const
{
    T length = Length();

    return Vector2T(x / length, y / length);
}

template <typename T>
constexpr T Vector3T<T>::LengthSquare() const
{
    return x * x + y * y + z * z;
}

template <typename T>
constexpr T Vector3T<T>::Length() const
{
    return Math::Sqrt(LengthSquare());
}

template <typename T>
constexpr Vector3T<T> Vector3T<T>::Normalize() const
{
    T length = Length();

    return Vector3T(x / length, y / length, z / length);
}

template <typename T>
constexpr T Vector4T<T>::LengthSquare() const
{
    return x * x + y * y + z * z + w * w;
}

template <typename T>
constexpr T Vector4T<T>::Length() const
{
    return Math::Sqrt(LengthSquare());
}

template <typename T>
constexpr Vector4T<T> Vector4T<T>::Normalize() const
{
    T length = Length();

    return Vector3T(x / length, y / length, z / length, w / length);
}

template <typename T>
constexpr Vector3T<T> Cross(const Vector3T<T>& a, const Vector3T<T>& b)
{
    return Vector3T<T>(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

template <typename T>
constexpr T Dot(const Vector2T<T>& a, const Vector2T<T>& b)
{
    return a.x * b.x + a.y * b.y;
}

template <typename T>
constexpr T Dot(const Vector3T<T>& a, const Vector3T<T>& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

}  // namespace red