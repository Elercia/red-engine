#include <catch2/catch.hpp>
#include <RedEngine/Core/Event/Delegate.hpp>

bool g_f_called = false;
bool g_lambda_called = false;

void f(int arg1, int arg2, float arg3)
{
    REQUIRE(arg1 == 1);
    REQUIRE(arg2 == 2);
    REQUIRE(arg3 <= 10);
    g_f_called = true;
}

TEST_CASE("Delegate", "[EVENT]")
{
    red::Delegate<int, int, float> delegate;

    delegate.Add(f);
    delegate.Add([&](int arg1, int arg2, float arg3) {
        REQUIRE(arg1 == 1);
        REQUIRE(arg2 == 2);
        REQUIRE(arg3 <= 10);
        g_lambda_called = true;
    });

    delegate(1, 2, 9.0f);
    REQUIRE(g_f_called);
    REQUIRE(g_lambda_called);
}
