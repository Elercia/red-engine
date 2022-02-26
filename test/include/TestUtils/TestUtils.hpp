#pragma once

#include <chrono>

namespace red
{
class DurationCounter
{
    using Clock = std::chrono::high_resolution_clock;

public:
    DurationCounter() = default;
    ~DurationCounter() = default;

    inline void Start();
    inline double Stop();

    inline double GetDuration();

private:
    Clock::time_point m_start{};
    Clock::time_point m_end{};
    bool m_isStarted{false};
};

struct DurationRAII
{
    DurationRAII(DurationCounter& dur) : m_dur(dur)
    {
        m_dur.Start();
    }

    ~DurationRAII()
    {
        m_dur.Stop();
    }
    
    DurationCounter& m_dur;
};
}  // namespace red

#include "inl/TestUtils.inl"