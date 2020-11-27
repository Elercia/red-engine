namespace red
{
template <typename T>
constexpr T Math::Clamp(T value, T min, T max)
{
    return Max(min, Min(max, value));
}

template <typename T>
constexpr T Math::Min(T l, T r)
{
    return l < r ? l : r;
}

template <typename T>
constexpr T Math::Max(T l, T r)
{
    return l > r ? l : r;
}

constexpr float Math::Clamp01(float value) { return Clamp(value, 0.F, 1.F); }
constexpr double Math::Clamp01(double value) { return Clamp(value, 0., 1.); }

template <typename T>
constexpr bool Math::Between(T value, T lValue, T rValue)
{
    return value >= lValue && value <= rValue;
}

constexpr int Math::NextPowerOf2(int n)
{
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;

    return n;
}

}  // namespace red