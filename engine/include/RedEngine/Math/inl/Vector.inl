#include "RedEngine/Utils/Types.hpp"

namespace red
{
template <typename T>
Vector2T<T> Vector2T<T>::operator+(const Vector2T<T>& other) const
{
    Vector2T<T> value;
    value.x = x + other.x;
    value.y = y + other.y;

    return value;
}

template <typename T>
Vector2T<T> Vector2T<T>::operator-(const Vector2T<T>& other) const
{
    Vector2T<T> value;
    value.x = x - other.x;
    value.y = y - other.y;

    return value;
}

template <typename T>
Vector2T<T> Vector2T<T>::operator*(const Vector2T<T>& other) const
{
    Vector2T<T> value;
    value.x = x * other.x;
    value.y = y * other.y;

    return value;
}

template <typename T>
Vector2T<T> Vector2T<T>::operator*(T scalar) const
{
    Vector2T<T> value;
    value.x = x * scalar;
    value.y = y * scalar;

    return value;
}

template <typename T>
T& Vector4T<T>::operator[](uint8 i)
{
    return (&x)[i];
}

template <typename T>
const T& Vector4T<T>::operator[](uint8 i) const
{
    return (&x)[i];
}

}  // namespace red