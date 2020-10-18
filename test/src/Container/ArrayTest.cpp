#include <RedEngine/Core/Container/Array.hpp>
#include <catch2/catch.hpp>

using namespace red;

TEST_CASE("Array push back", "[Container]")
{
    Array<int> intArray;
    REQUIRE(intArray.empty());

    for (int i = 0; i < 100; i++)
        intArray.push_back(i);

    REQUIRE(intArray.size() == 100);

    for (int i = 0; i < 100; i++)
    {
        int value = intArray[i];
        REQUIRE(value == i);
    }
}

TEST_CASE("Array performance", "[Container]")
{
    Array<int> intArray;
    REQUIRE(intArray.empty());

    std::vector<int> intVector;

    for (int i = 0; i < 100; i++)
        intArray.push_back(i);
}