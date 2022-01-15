#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Math/MatrixFunctions.hpp"
#include "RedEngine/Math/Vector.hpp"

#include <catch2/catch.hpp>
#include <iostream>

#include "TestModule.hpp"

TEST_CASE("Matrix initialization", "[MATH]")
{
    SECTION("Identity Constexpr")
    {
        constexpr Matrix44 matrix = Matrix44::Identity();

        REQUIRE(matrix(0, 0) == 1.0f);
        REQUIRE(matrix(1, 1) == 1.0f);
        REQUIRE(matrix(2, 2) == 1.0f);
        REQUIRE(matrix(3, 3) == 1.0f);
    }

    SECTION("Identity")
    {
        Matrix44 matrix = Matrix44::Identity();

        REQUIRE(matrix(0, 0) == 1.0f);
        REQUIRE(matrix(1, 1) == 1.0f);
        REQUIRE(matrix(2, 2) == 1.0f);
        REQUIRE(matrix(3, 3) == 1.0f);
    }

    SECTION("initializer list")
    {
        // clang-format off
		Matrix44 matrix = {
			1.f,	2.f,	3.f,	4.f,
			5.f,	6.f,	7.f,	8.f,
			9.f,	10.f,	11.f,	12.f,
			13.f,	14.f,	15.f,	16.f,
		};
        // clang-format on

        REQUIRE(matrix(0, 0) == 1.0f);
        REQUIRE(matrix(0, 1) == 2.0f);
        REQUIRE(matrix(0, 2) == 3.0f);
        REQUIRE(matrix(0, 3) == 4.0f);

        REQUIRE(matrix(1, 0) == 5.0f);
        REQUIRE(matrix(1, 1) == 6.0f);
        REQUIRE(matrix(1, 2) == 7.0f);
        REQUIRE(matrix(1, 3) == 8.0f);

        REQUIRE(matrix(2, 0) == 9.0f);
        REQUIRE(matrix(2, 1) == 10.0f);
        REQUIRE(matrix(2, 2) == 11.0f);
        REQUIRE(matrix(2, 3) == 12.0f);

        REQUIRE(matrix(3, 0) == 13.0f);
        REQUIRE(matrix(3, 1) == 14.0f);
        REQUIRE(matrix(3, 2) == 15.0f);
        REQUIRE(matrix(3, 3) == 16.0f);
    }
}

TEST_CASE("Matrix-scalar mul", "[MATH]")
{
    Matrix44 matrix = Matrix44::Identity();

    Matrix44 m2 = matrix * 2.0;

    REQUIRE(m2(0, 0) == 2.0f);
    REQUIRE(m2(1, 1) == 2.0f);
    REQUIRE(m2(2, 2) == 2.0f);
    REQUIRE(m2(3, 3) == 2.0f);
}

TEST_CASE("Matrix-vector mul", "[MATH]")
{
    Matrix44 matrix1 = Matrix44::Identity();
    Vector4 vec = {1.f, 2.f, 3.f, 4.f};

    Matrix44 m2 = matrix1 * vec;

    REQUIRE(m2(0, 0) == 1.0f);
    REQUIRE(m2(1, 1) == 2.0f);
    REQUIRE(m2(2, 2) == 3.0f);
    REQUIRE(m2(3, 3) == 4.0f);
}

TEST_CASE("Matrix-matrix mul", "[MATH]")
{
    Matrix44 matrix1 = Matrix44::Identity();
    Matrix44 matrix2 = Matrix44::Identity() * 2.f;

    Matrix44 m2 = matrix1 * matrix2;

    REQUIRE(m2(0, 0) == 2.0f);
    REQUIRE(m2(1, 1) == 2.0f);
    REQUIRE(m2(2, 2) == 2.0f);
    REQUIRE(m2(3, 3) == 2.0f);
}

TEST_CASE("Matrix det", "[MATH]")
{
    SECTION("2x2")
    {
        // clang-format off
    	Matrix22 a = {	1.f, 2.f,
    					3.f, 4.f};
        // clang-format on

        REQUIRE(a.Det() == -2.f);
    }

    SECTION("3x3")
    {
        // clang-format off
    	Matrix33 a = {	1.f, 	3.f, 	5.f,
    					7.f, 	1.f, 	11.f,
    					13.f, 	15.f, 	17.f, };
        // clang-format on

        REQUIRE(a.Det() == 384.f);
    }

    SECTION("4x4")
    {
        // clang-format off
    	Matrix44 a = {	9.f, 	2.f, 	2.f,	3.f,
    					7.f, 	6.f, 	1.f,	7.f,
    					9.f, 	4.f, 	7.f, 	3.f,
    					8.f, 	8.f, 	4.f, 	0.f, };
        // clang-format on

        REQUIRE(a.Det() == -1680.f);
    }
}

TEST_CASE("Matrix inverse", "[MATH]")
{
    SECTION("2x2")
    {
        // clang-format off
    	Matrix22 a = {	1.f, 2.f,
    					3.f, 4.f};

		Matrix22 res = {	-2.f, 		1.f,
    						3.f/2.f, 	-1.f/2.f};
        // clang-format on

        Matrix22 inv = a.Inverse();

        REQUIRE(inv.EqualsEpsilon(res, 0.1f));
    }

    SECTION("3x3")
    {
        // clang-format off
    	Matrix33 a = {	1.f, 	3.f, 	5.f,
    					7.f, 	1.f, 	11.f,
    					13.f, 	15.f, 	17.f, };

    	Matrix33 res = {	-37.f/96.f, 	1.f/16.f, 	7.f/96.f,
    						1.f/16.f, 		-1.f/8.f, 	1.f/16.f,
    						23.f/96.f, 		1.f/16.f, 	-5.f/96.f };
        // clang-format on

        Matrix33 inv = a.Inverse();

        REQUIRE(inv.EqualsEpsilon(res, 0.1f));
    }

    SECTION("4x4")
    {
        // clang-format off
    	Matrix44 a = {	9.f, 	2.f, 	2.f,	3.f,
    					7.f, 	6.f, 	1.f,	7.f,
    					9.f, 	4.f, 	7.f, 	3.f,
    					8.f, 	8.f, 	4.f, 	0.f, };

    	Matrix44 res = {	41.f/210.f, 	-2.f/35.f, 		-13.f/210.f,	1.f/40.f,
    						-5.f/42.f, 		1.f/14.f, 		-1.f/21.f,		1.f/8.f,
    						-16.f/105.f, 	-1.f/35.f, 		23.f/105.f, 	-1.f/20.f,
    						-1.f/14.f, 		1.f/17.f, 		1.f/14.f, 		-1.f/8.f };
        // clang-format on

        Matrix44 inv = a.Inverse();

        REQUIRE(inv.EqualsEpsilon(res, 0.1f));
    }

    SECTION("InvInv")
    {
        // clang-format off
    	Matrix22 a = {	1.f, 2.f,
    					3.f, -4.f};
    	Matrix33 b = {	1.f, 	3.f, 	5.f,
    					7.f, 	1.f, 	-11.f,
    					13.f, 	15.f, 	17.f, };				
    	Matrix44 c = {	9.f, 	-2.f, 	2.f,	3.f,
    					7.f, 	6.f, 	1.f,	-7.f,
    					-9.f, 	4.f, 	-7.f, 	3.f,
    					8.f, 	8.f, 	4.f, 	0.f, };
        // clang-format on

        REQUIRE(a.Inverse().Inverse().EqualsEpsilon(a, 0.1f));
        REQUIRE(b.Inverse().Inverse().EqualsEpsilon(b, 0.1f));
        REQUIRE(c.Inverse().Inverse().EqualsEpsilon(c, 0.1f));
    }
}

TEST_CASE("Matrix transpose", "[MATH]")
{
    SECTION("2x2")
    {
        // clang-format off
    	Matrix22 a = {	1.f, 2.f,
    					3.f, 4.f };

		Matrix22 res = {	1.f, 	3.f,
    						2.f, 	4.f };
        // clang-format on

        Matrix22 tra = a.Transpose();

        REQUIRE(tra == res);
    }

    SECTION("3x3")
    {
        // clang-format off
    	Matrix33 a = {	1.f, 	2.f, 	3.f,
    					4.f, 	5.f, 	6.f,
    					7.f, 	8.f, 	9.f, };

    	Matrix33 res = {	1.f, 	4.f, 	7.f,
    						2.f, 	5.f, 	8.f,
    						3.f, 	6.f, 	9.f };
        // clang-format on

        Matrix33 tra = a.Transpose();

        REQUIRE(tra == res);
    }

    SECTION("4x4")
    {
        // clang-format off
    	Matrix44 a = {	1.f, 	2.f, 	3.f,	4.f,
    					5.f, 	6.f, 	7.f,	8.f,
    					9.f, 	10.f, 	11.f, 	12.f,
    					13.f, 	14.f, 	15.f, 	16.f, };

    	Matrix44 res = {	1.f, 	5.f, 	9.f,	13.f,
    						2.f, 	6.f, 	10.f,	14.f,
    						3.f, 	7.f, 	11.f, 	15.f,
    						4.f, 	8.f, 	12.f, 	16.f };
        // clang-format on

        Matrix44 tra = a.Transpose();

        REQUIRE(tra == res);
    }
}