#include <RedEngine/Core/Container/Array.hpp>
#include <catch2/catch.hpp>

#include "TestUtils/TestUtils.hpp"

using namespace red;

TEST_CASE("Array push back", "[Container]")
{
    Array<int> intArray;
    REQUIRE(intArray.empty());

    for (int i = 0; i < 100; i++)
        intArray.push_back(i);

    REQUIRE(intArray.size() == 100);
    REQUIRE(intArray.capacity() == Math::NextPowerOf2(100));

    for (int i = 0; i < 100; i++)
    {
        int value = intArray[i];
        REQUIRE(value == i);
    }
}

TEST_CASE("Array accessors", "[Container]")
{
    Array<int> arr;
    REQUIRE(arr.empty());

    for (int i = 0; i < 100; i++)
        arr.push_back(i);

    REQUIRE(arr.size() == 100);

    REQUIRE(arr.front() == *arr.begin());
    REQUIRE(arr.back() == *(arr.end() - 1));

    for (int i = 0; i < 100; i++)
    {
        REQUIRE(arr[i] == arr.at(i));
    }
}

TEST_CASE("Array performance", "[Container]")
{
    DurationCounter arrayCtr;
    DurationCounter stdCtr;

    // Array perf
    {
        arrayCtr.Start();

        Array<int> intArray;
        REQUIRE(intArray.empty());

        for (int i = 0; i < 10000; i++)
            intArray.push_back(i);

        arrayCtr.Stop();
    }

    // std perf
    {
        stdCtr.Start();

        std::vector<int> intVector;

        for (int i = 0; i < 10000; i++)
            intVector.push_back(i);

        stdCtr.Stop();
    }

    REQUIRE(arrayCtr.GetDuration() < stdCtr.GetDuration());
}