#pragma once

#include "RedEngine/RedEngineBase.hpp"

namespace red
{
namespace Math
{
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

    constexpr int NextPowerOf2(int n);

    template <typename T>
    void SetBit(T& value, T bit);

    template <typename T>
    bool HasBit(const T& value, T bit);
};  // namespace Math
}  // namespace red

#include "inl/Math.inl"