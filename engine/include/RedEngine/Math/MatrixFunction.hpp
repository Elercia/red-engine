#pragma once

#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Math/Vector.hpp"

namespace red
{
namespace Math
{
	Matrix44 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);

	Matrix44 Translate(const Matrix44& mat, const Vector3& trans );
	Matrix44 Rotate(const Matrix44& mat, const Vector3& angles );
	Matrix44 Scale(const Matrix44& mat, const Vector3& scales );
}
}