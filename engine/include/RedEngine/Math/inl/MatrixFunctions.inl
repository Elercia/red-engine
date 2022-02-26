namespace red
{
namespace Math
{
	Matrix44 Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		// clang-format off
		Matrix44 ortho = {
			2 / (right - left), 0.f, 0.f, 		-((right+left) / (right-left)),
			0.f, 2.f / (top - bottom), 0.f, 	-((top+bottom) / (top-bottom)),
			0.f, 0.f, -2.f / (zFar- zNear) , 	-((zFar+zNear) / (zFar-zNear)),
			0.f, 0.f, 0.f, 						1.f,
		};
		// clang-format on

		return ortho;
	}

	Matrix44 Translate(const Matrix44& mat, const Vector3& trans )
	{
		// clang-format off
		Matrix44 translationMatrix = {
			1.f, 0.f, 0.f, trans.x,
			0.f, 1.f, 0.f, trans.y,
			0.f, 0.f, 1.f, trans.z,
			0.f, 0.f, 0.f, 1.f,
		};
		// clang-format on

		return translationMatrix * mat;
	}

	Matrix44 Rotate(const Matrix44& mat, const Vector3& angles )
	{
		float cosX = Cos(angles.x);
		float sinX = Sin(angles.x);
		float cosY = Cos(angles.y);
		float sinY = Sin(angles.y);
		float cosZ = Cos(angles.z);
		float sinZ = Sin(angles.z);

		// clang-format off
		Matrix44 rotationMatrixX = {
			1.f, 		0.f, 		0.f, 		0.f,
			0.f, 		cosX, 		-sinX, 		0.f,
			0.f, 		sinX, 		cosX,		0.f,
			0.f, 		0.f, 		0.f, 		1.f,
		};
		Matrix44 rotationMatrixY = {
			cosY, 		0.f, 		sinY, 		0.f,
			0.f, 		1.f, 		0.f, 		0.f,
			-sinY, 		0.f, 		cosY,		0.f,
			0.f, 		0.f, 		0.f, 		1.f,
		};
		Matrix44 rotationMatrixZ = {
			cosZ, 		-sinZ, 		0.f, 		0.f,
			sinZ, 		cosZ, 		0.f, 		0.f,
			0.f, 		0.f, 		1.f,		0.f,
			0.f, 		0.f, 		0.f, 		1.f,
		};
		// clang-format on

		return rotationMatrixX * rotationMatrixY * rotationMatrixZ * mat;
	}

	Matrix44 Scale(const Matrix44& mat, const Vector3& scales )
	{
		// clang-format off
		Matrix44 scaleMatrix = {
			scales.x, 	0.f, 		0.f, 		0.f,
			0.f, 		scales.y, 	0.f, 		0.f,
			0.f, 		0.f, 		scales.z,	0.f,
			0.f, 		0.f, 		0.f, 		1.f,
		};
		// clang-format on

		return scaleMatrix * mat;
	}
}
}