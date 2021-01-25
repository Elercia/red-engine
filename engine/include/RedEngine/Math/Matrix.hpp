#pragma once

#include "RedEngine/RedEngineBase.hpp"

#include <cstdlib>
namespace red
{
class Matrix4
{
public:
    Matrix4();
    ~Matrix4() = default;

    float& operator()(std::size_t i, std::size_t j);

public:
    static Matrix4 MakeOrthographic(float left, float right, float bottom, float top, float pNear, float pFar);

private:
    float m_data[4][4]{0};
};
}  // namespace red
