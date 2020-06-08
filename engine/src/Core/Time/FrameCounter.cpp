
#include <RedEngine/Core/Time/FrameCounter.hpp>
#include <numeric>
#include <RedEngine/Debug/Logger/Logger.hpp>

namespace red
{
FrameCounter::FrameCounter()
    : _lastFrameTimePoint(Clock::now()), m_frameBuffer(), m_currentFrameBufferIndex(0)
{
}

float FrameCounter::Update()
{
    auto currentTime = Clock::now();

    // Store the delta time in seconds
    std::chrono::duration<float> diff = currentTime - _lastFrameTimePoint;

    float deltaTime = diff.count();

    m_frameBuffer[m_currentFrameBufferIndex] = deltaTime;
    m_currentFrameBufferIndex = (m_currentFrameBufferIndex + 1U) % m_frameBuffer.size();

    _lastFrameTimePoint = currentTime;

    float meanDeltaTime =
        std::accumulate(m_frameBuffer.begin(), m_frameBuffer.end(), 0.F, std::plus<float>()) /
        m_frameBuffer.size();  // calculate the mean of delta times

    return meanDeltaTime;
}

}  // namespace red
