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

template <class T>
red::Vector2T<T>::operator b2Vec2() const
{
    static_assert(std::is_same_v<T, float>, "Conversion to b2Vec2 only work with Vector 2 float");

    return b2Vec2(x, y);
}

template <typename T>
Vector2T<T>::Vector2T(b2Vec2 box2DVec) : Vector2T(box2DVec.x, box2DVec.y)
{
    static_assert(std::is_same_v<T, float>,
                  "Conversion from box2D is only available for float vector");
}

}  // namespace red