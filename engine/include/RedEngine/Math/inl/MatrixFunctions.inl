namespace red
{
namespace Math
{
    Matrix44 Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
    {
        // clang-format off
		Matrix44 ortho = {
			2.f / (right - left),               0.f,                                0.f,                                0.f,
			0.f,                                2.f / (top - bottom),               0.f, 	                            0.f,
			0.f,                                0.f,                                -2.f / (zFar- zNear),               0.f,
			-((right+left) / (right-left)),     -((top+bottom) / (top-bottom)),     -((zFar+zNear) / (zFar-zNear)),     1.f,
		};
        // clang-format on

        return ortho;
    }

    // from GLM code
    Matrix44 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
    {
        Vector3 f = (center - eye).Normalize();
        Vector3 u = up.Normalize();
        Vector3 s = Cross(f, u).Normalize();
        u = Cross(s, f);

        Matrix44 Result;
        Result(0, 0) = s.x;
        Result(1, 0) = s.y;
        Result(2, 0) = s.z;
        Result(0, 1) = u.x;
        Result(1, 1) = u.y;
        Result(2, 1) = u.z;
        Result(0, 2) = -f.x;
        Result(1, 2) = -f.y;
        Result(2, 2) = -f.z;
        Result(3, 0) = -Dot(s, eye);
        Result(3, 1) = -Dot(u, eye);
        Result(3, 2) = Dot(f, eye);
        return Result;
    }

    Matrix44 Translate(const Matrix44& mat, const Vector3& trans)
    {
        // clang-format off
		Matrix44 translationMatrix = {
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			trans.x, trans.y, trans.z, 1.f,
		};
        // clang-format on

        return mat * translationMatrix;
    }

    Matrix33 Translate(const Matrix33& mat, const Vector2& trans)
    {
        // clang-format off
		Matrix33 translationMatrix = {
			1.f,        0.f,        0.f,
			0.f,        1.f,        0.f,
			trans.x,    trans.y,    1.f,
		};
        // clang-format on

        return mat * translationMatrix;
    }

    Matrix33 Rotate(const Matrix33& mat, float angle)
    {
        float cosTeta = Cos(angle);
        float sinTeta = Sin(angle);

        // clang-format off
		Matrix33 rotation = {
			cosTeta,  sinTeta, 0,
			-sinTeta, cosTeta, 0,
			0, 0, 1
		};
        // clang-format on

        return mat * rotation;
    }

    Matrix44 Rotate(const Matrix44& mat, const Vector3& angles)
    {
        float cosX = Cos(angles.x);
        float sinX = Sin(angles.x);
        float cosY = Cos(angles.y);
        float sinY = Sin(angles.y);
        float cosZ = Cos(angles.z);
        float sinZ = Sin(angles.z);
        //TODO row major
        // clang-format off
		Matrix44 rotationMatrixX = {
			1.f, 		0.f, 		0.f, 		0.f,
			0.f, 		cosX, 		sinX, 		0.f,
			0.f, 		-sinX, 		cosX,		0.f,
			0.f, 		0.f, 		0.f, 		1.f,
		};
		Matrix44 rotationMatrixY = {
			cosY, 		0.f, 		-sinY, 		0.f,
			0.f, 		1.f, 		0.f, 		0.f,
			sinY, 		0.f, 		cosY,		0.f,
			0.f, 		0.f, 		0.f, 		1.f,
		};
		Matrix44 rotationMatrixZ = {
			cosZ, 		sinZ, 		0.f, 		0.f,
			-sinZ, 		cosZ, 		0.f, 		0.f,
			0.f, 		0.f, 		1.f,		0.f,
			0.f, 		0.f, 		0.f, 		1.f,
		};
        // clang-format on

        return mat * rotationMatrixX * rotationMatrixY * rotationMatrixZ;
    }

    Matrix33 Scale(const Matrix33& mat, const Vector2& scales)
    {
        // clang-format off
		Matrix33 scaleMatrix = {
			scales.x, 	0.f, 		0.f, 	
			0.f, 		scales.y, 	0.f, 	
			0.f, 		0.f, 		1.f,
		};
        // clang-format on

        return mat * scaleMatrix;
    }

    Matrix44 Scale(const Matrix44& mat, const Vector3& scales)
    {
        // clang-format off
		Matrix44 scaleMatrix = {
			scales.x, 	0.f, 		0.f, 		0.f,
			0.f, 		scales.y, 	0.f, 		0.f,
			0.f, 		0.f, 		scales.z,	0.f,
			0.f, 		0.f, 		0.f, 		1.f,
		};
        // clang-format on

        return mat * scaleMatrix;
    }
}  // namespace Math
}  // namespace red