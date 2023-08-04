#pragma once

#include "RedEngine/Math/Math.hpp"

#include <marl/scheduler.h>
#include <marl/thread.h>
#include <marl/waitgroup.h>

namespace red
{
class Thread
{
public:
    friend class ThreadScheduler;
    friend class Engine;

    static const Thread& GetCurrentThread();
    static void InitMainThread();

    Thread();

    int GetId() const;
    const char* GetName() const;

private:
    Thread(int threadId, const char* name);

private:
    int m_threadId;
    const char* m_name;

    static int s_nextThreadId;

private:
    Thread(const Thread&) = delete;
    Thread(Thread&&) = delete;

    Thread& operator=(const Thread&) = delete;
    Thread& operator=(Thread&&) = default;
};

struct ThreadAllocator : public marl::Allocator
{
    // Inherited via Allocator
    virtual marl::Allocation allocate(const marl::Allocation::Request&) override;
    virtual void free(const marl::Allocation&) override;
};

struct WaitGroup
{
    WaitGroup(int taskCount);

    WaitGroup(const WaitGroup& other) = default;
    WaitGroup(WaitGroup&& other) = default;

    void Done() const;
    void Wait() const;

private:
    marl::WaitGroup m_internal;
};

class ThreadScheduler
{
public:
    struct WorkRange
    {
        int start;
        int end;
    };
    using SplitTaskFunc = std::function<void(const WorkRange&, int /*taskId*/)>;
    using TaskFunc = std::function<void()>;

public:
    ThreadScheduler();

    void Init();

    void Finalize();

    int GetWorkerCount() const;

    WaitGroup SplitWorkLoad(int numberOfParts, SplitTaskFunc&& func);  // TODO r value ?
    void Schedule(TaskFunc&& func);

    ThreadAllocator m_allocator;
    marl::Scheduler* m_scheduler;
};
}  // namespace red