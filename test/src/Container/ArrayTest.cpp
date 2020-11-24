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

    intArray.clear();

    REQUIRE(intArray.size() == 0);
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

    int i = 0;
    for (auto elem : arr)
    {
        REQUIRE(elem == arr.at(i));
        i++;
    }
}

TEST_CASE("Array memory shrink/reserve", "[Container]")
{
    Array<int> arr;
    REQUIRE(arr.empty());

    for (int i = 0; i < 100; i++)
        arr.push_back(i);

    REQUIRE(arr.size() == 100);
    REQUIRE(arr.capacity() != 100);

    arr.shrink_to_fit();

    REQUIRE(arr.capacity() == 100);

    arr.reserve(200);
    REQUIRE(arr.capacity() == 200);
    REQUIRE(arr.size() == 100);

    for (int i = 0; i < 100; i++)
        arr.push_back(i);

    REQUIRE(arr.capacity() == 200);
    REQUIRE(arr.size() == 200);
}

TEST_CASE("Array resize", "[Container]")
{
    Array<int> arr;
    REQUIRE(arr.empty());

    for (int i = 0; i < 10; i++)
        arr.push_back(i);

    REQUIRE(arr.size() == 10);

    arr.resize(20);
    REQUIRE(arr.size() == 20);

    arr.resize(20);
    REQUIRE(arr.size() == 20);

    arr.resize(30, 1000);
    REQUIRE(arr.size() == 30);

    for (int i = 20; i < 30; i++)
        REQUIRE(arr[i] == 1000);
}

int s_destructedCount = 0;

class ArrayTestStruct
{
public:
    explicit ArrayTestStruct(int i, int j = 0, const char* c = "") : value(i), j(j), c(c) {}
    ~ArrayTestStruct() { s_destructedCount++; }

    ArrayTestStruct(const ArrayTestStruct&) = default;
    ArrayTestStruct& operator=(const ArrayTestStruct&) = default;

    ArrayTestStruct(ArrayTestStruct&&) = default;
    ArrayTestStruct& operator=(ArrayTestStruct&&) = default;

    int value;
    int j;
    const char* c;
};

TEST_CASE("Array of struct", "[Container]")
{
    s_destructedCount = 0;

    {
        Array<ArrayTestStruct> arr;

        for (int i = 0; i < 100; i++)
        {
            ArrayTestStruct a = ArrayTestStruct(i);
            arr.push_back(std::move(a));
        }

        REQUIRE(arr.size() == 100);
        REQUIRE(s_destructedCount == 100);  // The 100 "a" objects that get moved

        s_destructedCount = 0;

        for (int i = 0; i < 100; i++)
        {
            auto& elem = arr[i];
            REQUIRE(elem.value == i);
        }

        REQUIRE(s_destructedCount == 0);

        int i = 0;
        for (auto& elem : arr)
        {
            REQUIRE(i == elem.value);
            i++;
        }

        REQUIRE(s_destructedCount == 0);

        {
            i = 0;
            const Array<ArrayTestStruct>& ref = arr;
            for (auto& elem : ref)
            {
                REQUIRE(i == elem.value);
                i++;
            }
        }

        REQUIRE(s_destructedCount == 0);

        arr.pop_back();

        REQUIRE(s_destructedCount == 1);
    }

    REQUIRE(s_destructedCount == 100);
}

TEST_CASE("Array erase", "[Container]")
{
    Array<int> arr{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(arr.size() == 10);

    auto itTest2 = arr.erase(arr.begin());
    REQUIRE(std::find(arr.begin(), arr.end(), 0) == arr.end());
    REQUIRE(arr.size() == 9);

    auto itTest = arr.erase(arr.begin() + 2, arr.begin() + 5);

    REQUIRE(arr.size() == 6);
    REQUIRE(std::find(arr.begin(), arr.end(), 3) == arr.end());
    REQUIRE(std::find(arr.begin(), arr.end(), 4) == arr.end());
    REQUIRE(std::find(arr.begin(), arr.end(), 5) == arr.end());

    // Erase all even numbers (C++11 and later)
    for (auto it = arr.begin(); it != arr.end();)
    {
        if (*it % 2 == 0)
        {
            it = arr.erase(it);
        }
        else
        {
            ++it;
        }
    }

    REQUIRE(arr.size() == 3);
    REQUIRE(std::find(arr.begin(), arr.end(), 1) != arr.end());
    REQUIRE(std::find(arr.begin(), arr.end(), 7) != arr.end());
    REQUIRE(std::find(arr.begin(), arr.end(), 9) != arr.end());
}

TEST_CASE("Array erase call destructor", "[Container]")
{
    s_destructedCount = 0;
    {
        Array<ArrayTestStruct> arr;
        for (int i = 0; i < 10; i++)
        {
            arr.emplace_back(i);
        }
        REQUIRE(s_destructedCount == 0);
        REQUIRE(arr.size() == 10);

        arr.erase(arr.begin());
        REQUIRE(arr.size() == 9);
        REQUIRE(s_destructedCount == 1);

        arr.erase(arr.begin() + 2, arr.begin() + 5);

        REQUIRE(arr.size() == 6);
        REQUIRE(s_destructedCount == 4);

        // Erase all even numbers (C++11 and later)
        for (auto it = arr.begin(); it != arr.end();)
        {
            if (it->value % 2 == 0)
            {
                it = arr.erase(it);
            }
            else
            {
                ++it;
            }
        }

        REQUIRE(arr.size() == 3);
    }

    REQUIRE(s_destructedCount == 10);
}

TEST_CASE("Array emplace", "[Container]")
{
    s_destructedCount = 0;
    {
        Array<ArrayTestStruct> arr;
        arr.reserve(100);

        for (int i = 0; i < 100; i++)
        {
            arr.emplace_back(i, (i % 2) * 23, "ARRRRR");
        }

        REQUIRE(s_destructedCount == 0);
    }

    REQUIRE(s_destructedCount == 100);
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
        REQUIRE(intVector.empty());

        for (int i = 0; i < 10000; i++)
            intVector.push_back(i);

        stdCtr.Stop();
    }

    REQUIRE(arrayCtr.GetDuration() < stdCtr.GetDuration());
}