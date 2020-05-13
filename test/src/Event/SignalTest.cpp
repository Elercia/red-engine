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

    SECTION("Activate / Deactivate slot & signal")
    {
        MyClass mc;

        red::Signal<int> signal;
        auto& slot = signal.Connect(&MyClass::op, &mc);

        slot.Deactivate();

        int a = 10;
        signal.emit(a);

        REQUIRE(mc.m_a == -1);

        slot.Activate();

        signal.Deactivate();

        signal.emit(a);

        REQUIRE(mc.m_a == -1);

        signal.Activate();
        signal.emit(a);
        REQUIRE(mc.m_a == 10);
    }
}