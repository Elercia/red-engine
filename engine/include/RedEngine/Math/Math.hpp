#pragma once

namespace red
{
class Mathf
{
private:
    Mathf() = default;

public:
    static constexpr double Min(double l, double r);
    static constexpr float Min(float l, float r);
    static constexpr double Max(double l, double r);
    static constexpr float Max(float l, float r);

    static constexpr double Clamp(double value, double min, double max);
    static constexpr float Clamp(float value, float min, float max);

    static constexpr float Clamp01(float value);
    static constexpr double Clamp01(double value);
};
}  // namespace red

#include "inl/Math.inl"