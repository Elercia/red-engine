#include "RedEngine/Core/Memory/LinearAllocator.hpp"

#include <algorithm>
#include <catch2/catch.hpp>

#include "TestModule.hpp"

TEST_CASE("Linear allocator", "[MEMORY]")
{
    LinearAllocator alloc(100 * sizeof(int));

    for (int i = 0; i < 100; i++)
    {
        int* p = alloc.Allocate<int>();
        REQUIRE(p != nullptr);
    }

    REQUIRE(alloc.Allocate<int>() == nullptr);

    alloc.Reset();

    REQUIRE(alloc.Allocate<int>(50) != nullptr);
    REQUIRE(alloc.Allocate<int>(50) != nullptr);
    REQUIRE(alloc.Allocate<int>(1) == nullptr);
}
