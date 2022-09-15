#pragma once

#include "RedEngine/Utils/Types.hpp"

#include <cstdint>

namespace red
{
struct Color
{
    constexpr Color();
    constexpr Color(uint8 r, uint8 g, uint8 b);
    constexpr Color(uint8 r, uint8 g, uint8 b, uint8 a);

    constexpr Vector4 AsVector4() const;

    uint8 r;
    uint8 g;
    uint8 b;
    uint8 a;
};

constexpr Color::Color() : r(0), g(0), b(0), a(255)
{
}

constexpr Color::Color(uint8 r, uint8 g, uint8 b) : r(r), g(g), b(b), a(255)
{
}

constexpr Color::Color(uint8 r, uint8 g, uint8 b, uint8 a) : r(r), g(g), b(b), a(a)
{
}

constexpr Vector4 Color::AsVector4() const
{
    return {(float) r / 255.f, (float) g / 255.f, (float) b / 255.f, (float) a / 255.f};
}

}  // namespace red

#include "inl/Color.inl"
