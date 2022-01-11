#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Math/Vector.hpp"

#include <catch2/catch.hpp>
#include <iostream>

#include "TestModule.hpp"

TEST_CASE("Matrix initialization", "[MATH]")
{
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
    Matrix44 matrix2 = Matrix44::Identity();

    Matrix44 m2 = matrix1 * matrix2;

    REQUIRE(m2(0, 0) == 1.0f);
    REQUIRE(m2(1, 1) == 1.0f);
    REQUIRE(m2(2, 2) == 1.0f);
    REQUIRE(m2(3, 3) == 1.0f);
}