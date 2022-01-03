#include "TestModule.hpp"

#include <RedEngine/Utils/TypesInfo.hpp>

#include <catch2/catch.hpp>
#include <iostream>

using namespace red;

struct MyType
{
};

template <typename T>
struct MyTypeTemplated
{
};

using TemplatedInt = MyTypeTemplated<int>;

TEST_CASE("Native type info", "[Types]")
{
    constexpr auto intTypeInfoConstexpr = TypeInfo<int>();
    auto intTypeInfo = TypeInfo<int>();
    int a = 0;

    auto varTypeInfo = RED_TYPE_INFO(a);

    REQUIRE(intTypeInfoConstexpr.typeId == intTypeInfo.typeId);
    REQUIRE(intTypeInfoConstexpr.name == intTypeInfo.name);
    REQUIRE(intTypeInfoConstexpr.name == "int");

    REQUIRE(intTypeInfoConstexpr.typeId == varTypeInfo.typeId);
    REQUIRE(intTypeInfoConstexpr.name == varTypeInfo.name);

    SECTION("int != float")
    {
        constexpr auto floatTypeInfoConstexpr = TypeInfo<float>();
        
        REQUIRE(intTypeInfoConstexpr.typeId != floatTypeInfoConstexpr.typeId);
        REQUIRE(intTypeInfoConstexpr.name != floatTypeInfoConstexpr.name);
        REQUIRE(floatTypeInfoConstexpr.name == "float");
    }
}

TEST_CASE("Custom types", "[Types]")
{
    constexpr auto MyTypeTypeInfoConstexpr = TypeInfo<MyType>();
    auto MyTypeTypeInfo = TypeInfo<MyType>();

    REQUIRE(MyTypeTypeInfoConstexpr.typeId == MyTypeTypeInfo.typeId);
    REQUIRE(MyTypeTypeInfoConstexpr.name == MyTypeTypeInfo.name);
    REQUIRE(MyTypeTypeInfoConstexpr.name == "MyType");
}

TEST_CASE("Templated types", "[Types]")
{
    constexpr auto TemplatedIntTypeInfoConstexpr = TypeInfo<TemplatedInt>();
    auto TemplatedIntTypeInfo = TypeInfo<TemplatedInt>();

    REQUIRE(TemplatedIntTypeInfoConstexpr.typeId == TemplatedIntTypeInfo.typeId);
    REQUIRE(TemplatedIntTypeInfoConstexpr.name == TemplatedIntTypeInfo.name);
    REQUIRE(TemplatedIntTypeInfoConstexpr.name == "MyTypeTemplated<int>");
}