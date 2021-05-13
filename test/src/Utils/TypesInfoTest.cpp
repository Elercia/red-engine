
#include <RedEngine/Utils/TypesInfo.hpp>

#include <catch2/catch.hpp>
#include <iostream>

using namespace red;


struct MyType
{

};

TEST_CASE("Native type info", "[Types]")
{
    constexpr auto intTypeInfoConstexpr = TypeInfo<int>();
    auto intTypeInfo = TypeInfo<int>();

    REQUIRE(intTypeInfoConstexpr.typeId == intTypeInfo.typeId);
    REQUIRE(intTypeInfoConstexpr.name == intTypeInfo.name);
    REQUIRE(intTypeInfoConstexpr.name == "int");

    std::cout << "\n\n\n--->" << intTypeInfoConstexpr.name << "<---\n\n\n" << std::endl;
}

TEST_CASE("Custom types", "[Types]")
{
    constexpr auto MyTypeTypeInfoConstexpr = TypeInfo<MyType>();
    auto MyTypeTypeInfo = TypeInfo<MyType>();

    REQUIRE(MyTypeTypeInfoConstexpr.typeId == MyTypeTypeInfo.typeId);
    REQUIRE(MyTypeTypeInfoConstexpr.name == MyTypeTypeInfo.name);
    REQUIRE(MyTypeTypeInfoConstexpr.name == "MyType");

    std::cout << "\n\n\n--->" << MyTypeTypeInfoConstexpr.name << "<---\n\n\n" << std::endl;
}