#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"

#include <catch2/catch.hpp>
#include <vector>

#include "TestModule.hpp"
#include "TestUtils/TestUtils.hpp"

using namespace red;

#ifdef RED_USE_ARRAY

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
    Array<int>::size_type cap = arr.capacity();
    REQUIRE(cap >= 200);
    REQUIRE(arr.size() == 100);

    for (int i = 0; i < 100; i++)
        arr.push_back(i);

    REQUIRE(arr.capacity() == cap);
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
    explicit ArrayTestStruct(int i, int j = 0, const char* c = "") : value(i), j(j), c(c)
    {
    }
    ~ArrayTestStruct()
    {
        s_destructedCount++;
    }

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

    arr.erase(arr.begin());
    REQUIRE(std::find(arr.begin(), arr.end(), 0) == arr.end());
    REQUIRE(arr.size() == 9);

    arr.erase(arr.begin() + 2, arr.begin() + 5);

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
        REQUIRE(arr.size() == 10);

        arr.erase(arr.begin());
        REQUIRE(arr.size() == 9);

        arr.erase(arr.begin() + 2, arr.begin() + 5);

        REQUIRE(arr.size() == 6);

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

Array<std::string> GetArray()
{
    Array<std::string> ar;

    ar.push_back("Test1");
    ar.emplace_back("TEST2");

    return ar;
}

TEST_CASE("Array copy", "[Container]")
{
    Array<std::string> ar = GetArray();

    SECTION("equals")
    {
        REQUIRE(ar[0] == "Test1");
        REQUIRE(ar[1] == "TEST2");
    }

    SECTION("move")
    {
        Array<std::string> ar2 = std::move(ar);

        REQUIRE(ar2[0] == "Test1");
        REQUIRE(ar2[1] == "TEST2");
    }
}

TEST_CASE("Array benchmark", "[Container_Benchmark]")
{
    using namespace red;

    DurationCounter counterArray;
    DurationCounter counterVector;

    struct A
    {
        A() : d(0.0), f(0.f), i(0)
        {
        }

        A(double dd) : d(dd), f(0.f), i(0)
        {
        }

        double d;
        float f;
        int i;
    };

    // Array part
    {
        DurationRAII profiler(counterArray);

        Array<int> a;
        for (int i = 0; i < 30000; i++)
        {
            a.push_back(i);
            a.emplace_back(1);
        }

        Array<int> other = a;
        other.push_back(1);
        other = std::move(a);

        Array<int> b = other;
        Array<int> c(std::move(b));

        (void)c;

        Array<A> aaa;
        for (int i = 0; i < 30000; i++)
        {
            aaa.push_back(A(0.0));
            aaa.emplace_back(1.0);
        }

        Array<A> other2 = aaa;
        other2.push_back(A());
        other2 = std::move(aaa);

        Array<A> bbb = other2;
        Array<A> ccc(std::move(bbb));

        (void)ccc;
    }

    // vector part
    {
        DurationRAII profiler(counterVector);

        std::vector<int> a;
        for (int i = 0; i < 300000; i++)
        {
            a.push_back(i);
            a.emplace_back(1);
        }

        std::vector<int> other = a;
        other.push_back(1);
        other = std::move(a);

        std::vector<int> b = other;
        std::vector<int> c(std::move(b));

        (void)c;

        std::vector<A> aaa;
        for (int i = 0; i < 300000; i++)
        {
            aaa.push_back(A(0.0));
            aaa.emplace_back(1.0);
        }

        std::vector<A> other2 = aaa;
        other2.push_back(A());
        other2 = std::move(aaa);

        std::vector<A> bbb = other2;
        std::vector<A> ccc(std::move(bbb));

        (void)ccc;
    }

    std::cout << "Array timing : " << counterArray.GetDuration()<< "\nstd::vector timing : " << counterVector.GetDuration() << std::endl;

    REQUIRE(counterArray.GetDuration() <= counterVector.GetDuration());
}

#endif  // RED_USE_ARRAY