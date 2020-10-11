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
Vector2T<T> Vector2T<T>::operator*(T scalar) const
{
    Vector2T<T> value;
    value.x = x * scalar;
    value.y = y * scalar;

    return value;
}

}  // namespace red