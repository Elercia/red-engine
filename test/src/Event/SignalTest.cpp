#include <catch2/catch.hpp>
#include "RedEngine/Core/Event/Signal.hpp"
#include <SignalTest.hpp>

TEST_CASE("Signal/Slots connections", "[EVENT]")
{
    SECTION("Pong lambda")
    {
        bool isCalled = false;
        red::Signal<int> signal;
        signal.Connect([&](int i) { isCalled = true; });

        signal.emit(1);

        REQUIRE(isCalled);
    }

    SECTION("Pong method bind")
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
        auto slot = signal.Connect(&MyClass::op, &mc);

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

    SECTION("Copying slots")
    {
        MyClass mc;

        red::Signal<int> signal;

        red::Signal<int>::Slot slot;

        {
            auto firstSlot = signal.Connect(&MyClass::op, &mc);
            slot = firstSlot;
        }

        REQUIRE(slot.IsActive());

        signal.emit(10);

        REQUIRE(mc.m_a == 10);
    }
}