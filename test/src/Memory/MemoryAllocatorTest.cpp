#include "RedEngine/Core/Memory/LinearAllocator.hpp"
#include "RedEngine/Core/Memory/PoolAllocator.hpp"
#include "RedEngine/Utils/SystemInfo.hpp"

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

struct MyStruct
{
    int* m_inc;

    MyStruct(int* icc) : m_inc(icc)
    {
        (*m_inc)++;
    }

    ~MyStruct()
    {
        (*m_inc)--;
    }

    MyStruct(const MyStruct&) = delete;
    MyStruct(MyStruct&&) = delete;

    MyStruct& operator=(const MyStruct&) = delete;
    MyStruct& operator=(MyStruct&&) = delete;
};

TEST_CASE("Virtual pool allocator", "[MEMORY]")
{
    InitSystemInfo();

    VirtualPoolAllocator pool(sizeof(MyStruct), 100);

    int inc = 0;
    Array<MyStruct*> ptrs;

    for (int i = 0; i < 100; i++)
    {
        MyStruct* p = pool.Allocate<MyStruct>(&inc);
        REQUIRE(p != nullptr);

        ptrs.push_back(p);
    }

    REQUIRE(inc == 100);

    // "Shuffle"
    for (int i = 0; i < 100; i++)
    {
        ptrs[i] = ptrs[(i + 13) % 100];
    }

    for (int i = 50; i < 100; i++)
    {
        pool.Free(ptrs[i]);
    }
    ptrs.erase(ptrs.begin() + 50, ptrs.end());

    REQUIRE(inc == 50);

    for (int i = 0; i < 100; i++)
    {
        MyStruct* p = pool.Allocate<MyStruct>(&inc);
        REQUIRE(p != nullptr);

        ptrs.push_back(p);
    }
}
