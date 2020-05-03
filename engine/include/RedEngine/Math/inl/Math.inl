
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

}  // namespace red