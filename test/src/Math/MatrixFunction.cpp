#include "RedEngine/Math/Math.hpp"
#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Math/MatrixFunctions.hpp"
#include "RedEngine/Math/Vector.hpp"

#include <catch2/catch.hpp>
#include <iostream>

#include "TestModule.hpp"
#include "fmt/core.h"

TEST_CASE("Orthogonal_transformation", "[MATH]")
{
	Matrix44 m = Math::Ortho(0.f, 800.f, 0.f, 600.f, 0.01f, 100.f);
	
	Vector4 v0(0.f, 0.f, 0.f, 1.f);
	Vector4 v1(800.f, 600.f, 0.f, 1.f);

	Vector4 transformedv0 = m * v0;
	Vector4 transformedv1 = m * v1;

	fmt::print("v0 : {} {}\n", transformedv0.x, transformedv0.y);
	fmt::print("v1 : {} {}\n", transformedv1.x, transformedv1.y);

	REQUIRE(Math::EqualsEpsilon(transformedv0.x, -1.f, 0.01f));
	REQUIRE(Math::EqualsEpsilon(transformedv0.y, -1.f, 0.01f));

	REQUIRE(Math::EqualsEpsilon(transformedv1.x, 1.f, 0.01f));
	REQUIRE(Math::EqualsEpsilon(transformedv1.y, 1.f, 0.01f));
}