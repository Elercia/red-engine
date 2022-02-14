#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"

#include <catch2/catch.hpp>
#include <vector>

#include "TestModule.hpp"
#include "TestUtils/TestUtils.hpp"

using namespace red;

#ifdef RED_USE_MAP

TEST_CASE("Map Set / Get", "[Container]")
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

TEST_CASE("Map Initializer list", "[Container]")
{
    Map<std::string, int> m({{"ONE", 1}, {"TWO", 2}, {"THREE", 3}});

    REQUIRE(m.size() == 3);
    REQUIRE(m["ONE"] == 1);
    REQUIRE(m["TWO"] == 2);
    REQUIRE(m["THREE"] == 3);
}

TEST_CASE("Map a lot of keys", "[Container]")
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

TEST_CASE("Map colisions", "[Container]")
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

TEST_CASE("Map erase", "[Container]")
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

#endif  // RED_USE_ARRAY