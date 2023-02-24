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
    inline Matrix33 Translate(const Matrix33& mat, const Vector2& trans);

    inline Matrix44 Rotate(const Matrix44& mat, const Vector3& angles);
    inline Matrix33 Rotate(const Matrix33& mat, float angle);

    inline Matrix44 Scale(const Matrix44& mat, const Vector3& scales);
    inline Matrix33 Scale(const Matrix33& mat, const Vector2& scales);
}  // namespace Math
}  // namespace red

#include "inl/MatrixFunctions.inl"