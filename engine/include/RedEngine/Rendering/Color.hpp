#pragma once

#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Utils/Types.hpp"

#include <cstdint>

namespace red
{
struct Color
{
    constexpr Color();
    constexpr Color(float r, float g, float b);
    constexpr Color(float r, float g, float b, float a);

    constexpr Vector4 AsVector4() const;

    float r;
    float g;
    float b;
    float a;
};

constexpr Color::Color() : r(0), g(0), b(0), a(0.f)
{
}

constexpr Color::Color(float r, float g, float b) : r(r), g(g), b(b), a(0.f)
{
}

constexpr Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
{
}

constexpr Vector4 Color::AsVector4() const
{
    return {r, g, b, a};
}

}  // namespace red

#include "inl/Color.inl"
