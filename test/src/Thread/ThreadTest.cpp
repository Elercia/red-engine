#include "RedEngine/Thread/Thread.hpp"

#include <catch2/catch.hpp>

#include "TestModule.hpp"

using namespace red;

TEST_CASE("Basic sum", "[Thread]")
{
    ThreadScheduler scheduler;
    scheduler.Init();

    int elems[4321] = {0};
    int compareSum = 0;

    for (int i = 0; i < 4321; i++)
    {
        elems[i] = 1;
        compareSum += 1;
    }

    int* sumAr = new int[scheduler.GetWorkerCount()];
    auto wg = scheduler.SplitWorkLoad(4321,
                                      [sumAr, &elems](const ThreadScheduler::WorkRange& range, int taskId)
                                      {
                                          sumAr[taskId] = 0;
                                          for (int i = range.start; i < range.end; i++)
                                          {
                                              sumAr[taskId] += elems[i];
                                          }
                                      });
    wg.Wait();

    int sum = 0;
    for (int i = 0; i < scheduler.GetWorkerCount(); i++)
        sum += sumAr[i];

    REQUIRE(sum == compareSum);

    delete[] sumAr;

    scheduler.Finalize();
}

// We cannot guarantee the task will be runned on each thread
// But this will fail if some of the threads are not initialized
TEST_CASE("Thread struct initialized", "[Thread]")
{
    ThreadScheduler scheduler;
    scheduler.Init();

    const Thread** threads = new const Thread*[scheduler.GetWorkerCount()];

    auto wg = scheduler.SplitWorkLoad(scheduler.GetWorkerCount(),
                                      [threads](const ThreadScheduler::WorkRange& /*range*/, int taskId)
                                      { threads[taskId] = &Thread::GetCurrentThread(); });
    wg.Wait();

    for (int i = 0; i < scheduler.GetWorkerCount(); i++)
    {
        int threadId = threads[i]->GetId();
        REQUIRE(threadId != -1);
    }

    delete[] threads;
    scheduler.Finalize();
}