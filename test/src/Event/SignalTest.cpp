#include <catch2/catch.hpp>
#include <RedEngine/Event/Signal.hpp>
#include <SignalTest.hpp>

TEST_CASE("Signal/Slots connections", "[EVENT]")
{
    SECTION("Simple lambda")
    {
        bool isCalled = false;
        red::Signal<int> signal;
        signal.Connect([&](int i) { isCalled = true; });

        signal.emit(1);

        REQUIRE(isCalled);
    }

    SECTION("Simple method bind")
    {
        MyClass mc;

        red::Signal<int> signal;
        signal.Connect(&MyClass::op, &mc);

        int a = 10;
        signal.emit(a);

        REQUIRE(mc.m_a == 10);
    }
}