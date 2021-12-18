#pragma once


#include "RedEngine/Utils/Types.hpp"

#include <cstdint>

namespace red
{
struct Color
{
    constexpr Color(uint8 r, uint8 g, uint8 b);
    constexpr Color(uint8 r, uint8 g, uint8 b, uint8 a);

    uint8 r;
    uint8 g;
    uint8 b;
    uint8 a;
};

constexpr Color::Color(uint8 r, uint8 g, uint8 b) : r(r), g(g), b(b), a(255)
{
}

constexpr Color::Color(uint8 r, uint8 g, uint8 b, uint8 a) : r(r), g(g), b(b), a(a)
{
}

}  // namespace red

#include "inl/Color.inl"
