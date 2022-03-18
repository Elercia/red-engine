#pragma once

#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Math/Vector.hpp"

namespace red
{
namespace Math
{
    inline Matrix44 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
    inline Matrix44 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up);

    inline Matrix44 Translate(const Matrix44& mat, const Vector3& trans);
    inline Matrix44 Rotate(const Matrix44& mat, const Vector3& angles);
    inline Matrix44 Scale(const Matrix44& mat, const Vector3& scales);
}  // namespace Math
}  // namespace red

#include "inl/MatrixFunctions.inl"