#pragma once

#include <chrono>

#include "RedEngine/RedEngineBase.hpp"

namespace red
{
class DurationCounter
{
    using Clock = std::chrono::high_resolution_clock;

public:
    DurationCounter() = default;
    ~DurationCounter() = default;

    void Start();
    double Stop();

    double GetDuration();

private:
    Clock::time_point m_start{};
    Clock::time_point m_end{};
    bool m_isStarted{false};
};
}  // namespace red

#include "inl/TestUtils.inl"