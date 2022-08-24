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

constexpr float Math::Clamp01(float value)
{
    return Clamp(value, 0.F, 1.F);
}
constexpr double Math::Clamp01(double value)
{
    return Clamp(value, 0., 1.);
}

template <typename T>
constexpr bool Math::Between(T value, T lValue, T rValue)
{
    return value >= lValue && value <= rValue;
}

constexpr uint32 Math::NextPowerOf2(uint32 n)
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

template <typename T>
constexpr bool Math::EqualsEpsilon(T a, T b, T epsilon)
{
    if (a > b)
        return (a - b) <= epsilon;

    return (b - a) <= epsilon;
}

constexpr float Math::ToRadians(float degrees)
{
    return degrees * Math::PI / 180;
}

constexpr float Math::ToDegrees(float radians)
{
    return radians * 180 / Math::PI;
}

float Math::Sqrt(float f)
{
    return sqrt(f);
}

float Math::Cos(float f)
{
    return cos(f);
}

float Math::Sin(float f)
{
    return sin(f);
}

float Math::Tan(float f)
{
    return tan(f);
}


}  // namespace red
