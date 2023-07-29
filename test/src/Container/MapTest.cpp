#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"

#include <catch2/catch.hpp>
#include <vector>

#include "TestModule.hpp"
#include "TestUtils/TestUtils.hpp"

using namespace red;

#ifdef RED_USE_MAP

TEST_CASE("Map Set / Get", "[Map]")
{
    Map<std::string, int> m;

    REQUIRE(m.size() == 0);
    REQUIRE(m.empty());

    m.insert({"ONE", 1});
    m.insert({"TWO", 2});
    m.insert({"THREE", 3});

    REQUIRE(m.size() == 3);

    REQUIRE(m["ONE"] == 1);
    REQUIRE(m["TWO"] == 2);
    REQUIRE(m["THREE"] == 3);

    REQUIRE(m.size() == 3);
    m["ONE"] = 11;
    REQUIRE(m.size() == 3);

    REQUIRE(m["ONE"] == 11);
    REQUIRE(m["TWO"] == 2);
    REQUIRE(m["THREE"] == 3);
}

TEST_CASE("Map Initializer list", "[Map]")
{
    Map<std::string, int> m({{"ONE", 1}, {"TWO", 2}, {"THREE", 3}});

    REQUIRE(m.size() == 3);
    REQUIRE(m["ONE"] == 1);
    REQUIRE(m["TWO"] == 2);
    REQUIRE(m["THREE"] == 3);
}

TEST_CASE("Map a lot of keys", "[Map]")
{
    // Mainly to test delay, iterators and map usage
    Map<int, int> m;

    for (int i = 0; i < 3000; i++)
    {
        m.insert({i, i});
    }

    for (auto& keyValue : m)
    {
        REQUIRE(keyValue.first == keyValue.second);
    }

    for (int i = 0; i < 3000; i++)
    {
        REQUIRE(m[i] == i);
    }

    REQUIRE(m.size() == 3000);

    for (int i = 0; i < 3000; i++)
    {
        m[i] = i + 3000;
    }

    REQUIRE(m.size() == 3000);

    for (auto& keyValue : m)
    {
        REQUIRE(keyValue.second == (keyValue.first + 3000));
    }
}

TEST_CASE("Map colisions", "[Map]")
{
    Map<std::string, int> m;

    for (int i = 0; i < 3000; i++)
    {
        std::string s = fmt::format("{}", i);
        m.insert({s, i});
    }

    REQUIRE(m.size() == 3000);

    for (auto& p : m)
    {
        std::string s = fmt::format("{}", p.second);
        REQUIRE(s == p.first);
    }
}

TEST_CASE("Map erase", "[Map]")
{
    Map<int, int> m;

    for (int i = 0; i < 3000; i++)
    {
        m.insert({i, i});
    }
    REQUIRE(m.size() == 3000);

    for (int i = 0; i < 3000; i += 2)
    {
        m.erase(i);
    }
    REQUIRE(m.size() == 1500);

    for (int i = 1; i < 3000; i += 2)
    {
        REQUIRE(m[i] == i);
    }
    REQUIRE(m.size() == 1500);

    uint64 iter = 0;
    for (auto& p : m)
    {
        iter++;
        REQUIRE(p.first == p.second);
    }

    REQUIRE(iter == m.size());

    for (int i = 0; i < 3000; i += 2)
    {
        m.insert({i, i});
    }

    REQUIRE(m.size() == 3000);

    for (int i = 0; i < 3000; i++)
    {
        REQUIRE(m[i] == i);
    }
}

TEST_CASE("Map struct", "[Map]")
{
    struct TestStruct
    {
        int m_i;
        explicit TestStruct(int i) : m_i(i) {}
        TestStruct(const TestStruct& other) :m_i(other.m_i) {}
        TestStruct(TestStruct&& other) :m_i(std::exchange(other.m_i, -1)) {}

        TestStruct& operator=(const TestStruct& other) { m_i = other.m_i; return *this; }
        TestStruct& operator=(TestStruct&& other) { m_i = std::exchange(other.m_i, -1); return *this; }
    };

    Map<int, TestStruct> m;

    for (int i = 0; i < 3000; i++)
    {
        m.insert({i, TestStruct(i)});
    }
    REQUIRE(m.size() == 3000);

    for(auto p : m)
    {
        REQUIRE(p.first == p.second.m_i);
    }
}

//#define RED_TEST_BENCHMARK
#ifdef RED_TEST_BENCHMARK
#include <unordered_map>

TEST_CASE("Map benchmark", "[Map_Benchmark]")
{
    DurationCounter counterRed;
    DurationCounter counterStd;
    DurationCounter counterStdUnordered;

    const int iterationCount = 10'000'000;

    {
        DurationRAII profiler(counterRed);

        Map<std::string, int> m;

        for (int i = 0; i < iterationCount; i++)
        {
            std::string s = fmt::format("{}", i);
            m.insert({std::move(s), i});
        }

        for (auto& p : m)
        {
            std::string s = fmt::format("{}", p.second);
            REQUIRE(s == p.first);
        }

        for (int i = 0; i < iterationCount; i++)
        {
            std::string s = fmt::format("{}", i);
            m.erase(s);
        }
    }

    {
        DurationRAII profiler(counterStd);

        std::map<std::string, int> m;

        for (int i = 0; i < iterationCount; i++)
        {
            std::string s = fmt::format("{}", i);
            m.insert({std::move(s), i});
        }

        for (auto& p : m)
        {
            std::string s = fmt::format("{}", p.second);
            REQUIRE(s == p.first);
        }

        for (int i = 0; i < iterationCount; i++)
        {
            std::string s = fmt::format("{}", i);
            m.erase(s);
        }
    }

    {
        DurationRAII profiler(counterStdUnordered);

        std::unordered_map<std::string, int> m;

        for (int i = 0; i < iterationCount; i++)
        {
            std::string s = fmt::format("{}", i);
            m.insert({std::move(s), i});
        }

        for (auto& p : m)
        {
            std::string s = fmt::format("{}", p.second);
            REQUIRE(s == p.first);
        }

        for (int i = 0; i < iterationCount; i++)
        {
            std::string s = fmt::format("{}", i);
            m.erase(s);
        }
    }

    std::cout << "red::Map timing : " << counterRed.GetDuration() << "\nstd::map timing : " << counterStd.GetDuration()
              << "\nstd::unordered_map timing : " << counterStdUnordered.GetDuration() << std::endl;

    REQUIRE(counterRed.GetDuration() <= counterStd.GetDuration());
    REQUIRE(counterRed.GetDuration() <= counterStdUnordered.GetDuration());
}
#endif

#endif  // RED_USE_ARRAY