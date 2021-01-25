#include "RedEngine/Math/Matrix.hpp"

#include <cstring>

namespace red
{
Matrix4::Matrix4() { memset(m_data, 0, sizeof m_data); }

Matrix4 Matrix4::MakeOrthographic(float left, float right, float bottom, float top, float pNear, float pFar)
{
    // https://en.wikipedia.org/wiki/Orthographic_projection
    auto matrix = Matrix4();

    matrix.m_data[0][0] = 2.F / (right - left);
    matrix.m_data[0][1] = 0;
    matrix.m_data[0][2] = 0;
    matrix.m_data[0][2] = -(right + left) / (right - left);

    matrix.m_data[1][0] = 0;
    matrix.m_data[1][1] = 2.F / (top - bottom);
    matrix.m_data[1][2] = 0;
    matrix.m_data[1][2] = -(top + bottom) / (top - bottom);

    matrix.m_data[1][0] = 0;
    matrix.m_data[1][1] = 0;
    matrix.m_data[1][2] = -2.F / (pFar - pNear);
    matrix.m_data[1][2] = -(pFar + pNear) / (pFar - pNear);

    matrix.m_data[1][0] = 0;
    matrix.m_data[1][1] = 0;
    matrix.m_data[1][2] = 0;
    matrix.m_data[1][2] = 1;

    return matrix;
}

float& Matrix4::operator()(std::size_t i, std::size_t j) { return m_data[i][j]; }

}  // namespace red