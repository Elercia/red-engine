#pragma once

#include <RedEngine/RedEngineBase.hpp>

#include <chrono>
#include <array>

namespace red
{
constexpr uint8_t FrameCounterBufferSize = 10;

class FrameCounter
{
    using Clock = std::chrono::system_clock;

public:
    FrameCounter();
    ~FrameCounter() = default;

    float Update();

private:
    Clock::time_point _lastFrameTimePoint;
    std::array<float, FrameCounterBufferSize> m_frameBuffer;
    uint8_t m_currentFrameBufferIndex = 0;
};
}  // namespace red
