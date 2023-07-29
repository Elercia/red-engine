#include "RedEngine/Thread/Thread.hpp"

#include "RedEngine/Core/Configuration/CVar.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"

#include <algorithm>

namespace red
{
thread_local Thread sl_thread;
int Thread::s_nextThreadId = 0;

static CVar<int> s_wantedThreadCount("ThreadCount", "Engine_Thread", -1);

const Thread &Thread::GetCurrentThread()
{
    return sl_thread;
}

void Thread::InitMainThread()
{
    sl_thread = Thread(s_nextThreadId, "Main");
}

Thread::Thread() : m_threadId(-1), m_name(nullptr)
{
}

Thread::Thread(int threadId, const char *name) : m_threadId(threadId), m_name(name)
{
}

int Thread::GetId() const
{
    return m_threadId;
}

const char *Thread::GetName() const
{
    return m_name;
}

ThreadScheduler::ThreadScheduler() : m_scheduler(nullptr)
{
}

void ThreadScheduler::Init()
{
    auto config = marl::Scheduler::Config::allCores();
    if (s_wantedThreadCount.GetValue() != -1)
    {
        config.setWorkerThreadCount(s_wantedThreadCount);
    }

    // config.setAllocator(&m_allocator);
    config.workerThread.initializer = [](int /*workerId*/)
    {
        if (sl_thread.GetId() == -1)
            sl_thread = Thread(Thread::s_nextThreadId++, "Worker");

        PROFILER_THREAD(sl_thread.GetName());
    };

    Thread::InitMainThread();

    m_scheduler = new marl::Scheduler(config);
    m_scheduler->bind();
}

void ThreadScheduler::Finalize()
{
    m_scheduler->unbind();
    Thread::s_nextThreadId = 0;
}

int ThreadScheduler::GetWorkerCount() const
{
    return m_scheduler->config().workerThread.count;
}

WaitGroup ThreadScheduler::SplitWorkLoad(int numberOfParts, SplitTaskFunc &&func)
{
    auto workerCount = GetWorkerCount();

    int numberOfTasks = numberOfParts / workerCount + numberOfParts % workerCount;

    WaitGroup wg(workerCount);
    for (int i = 0; i < workerCount; i++)
    {
        marl::schedule(
            [=]
            {
                WorkRange range = {i * numberOfTasks, Math::Min(numberOfParts, (i + 1) * numberOfTasks)};
                func(range, i);
                wg.Done();
            });
    }

    return wg;
}

void ThreadScheduler::Schedule(TaskFunc &&func)
{
    marl::schedule(std::forward<TaskFunc>(func));
}

marl::Allocation ThreadAllocator::allocate(const marl::Allocation::Request &request)
{
    marl::Allocation alloc;

    alloc.request = request;
    alloc.ptr = red_malloc(request.size);

    return alloc;
}

void red::ThreadAllocator::free(const marl::Allocation &allocation)
{
    red_free(allocation.ptr);
}

WaitGroup::WaitGroup(int taskCount) : m_internal(taskCount)
{
}

void WaitGroup::Done() const
{
    m_internal.done();
}

void WaitGroup::Wait() const
{
    m_internal.wait();
}
}  // namespace red
