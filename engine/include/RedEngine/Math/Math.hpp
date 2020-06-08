#pragma once

namespace red
{
class Math
{
private:
    Math() = default;

public:
    template <typename T>
    static constexpr T Min(T l, T r);

    template <typename T>
    static constexpr T Max(T l, T r);

    template <typename T>
    static constexpr T Clamp(T value, T min, T max);

    static constexpr float Clamp01(float value);
    static constexpr double Clamp01(double value);

    template <typename T>
    static constexpr bool Between(T value, T lValue, T rValue);
};
}  // namespace red

#include "inl/Math.inl"