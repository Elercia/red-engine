#pragma once

namespace red
{
class Point
{
public:
    Point() : Point(0, 0) {}
    Point(int pX, int pY) : x(pX), y(pY) {}
    ~Point() = default;

    int x, y;
};
}  // namespace red
