#pragma once

#include "RedEngine/Utils/Types.hpp"

#include <cmath>

namespace red
{
namespace Math
{
    constexpr float PI = 3.14159265358979323846f;
    constexpr double PId = 3.14159265358979323846;

    template <typename T>
    constexpr T Min(T l, T r);

    template <typename T>
    constexpr T Max(T l, T r);

    template <typename T>
    constexpr T Clamp(T value, T min, T max);

    static constexpr float Clamp01(float value);
    constexpr double Clamp01(double value);

    template <typename T>
    constexpr bool Between(T value, T lValue, T rValue);

    inline float Sqrt(float f);
    constexpr uint32 NextPowerOf2(uint32 n);

    template <typename T>
    constexpr bool EqualsEpsilon(T a, T b, T epsilon);

    inline constexpr float ToRadians(float degrees);
    inline constexpr float ToDegrees(float radians);

    inline float Cos(float f);
    inline float Sin(float f);
    inline float Tan(float f);


}  // namespace Math
}  // namespace red

#include "inl/Math.inl"
