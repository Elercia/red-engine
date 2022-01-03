#include "RedEngine/Core/Time/Time.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Math/Math.hpp"

namespace red
{
float Time::s_timeScale = 1.F;
float Time::s_deltaTime = 0.F;

float Time::TimeScale()
{
    return s_timeScale;
}

void Time::SetTimeScale(float newTimeScale)
{
    s_timeScale = Math::Clamp(newTimeScale, 0.F, 2.F);
}

float Time::DeltaTime(bool scaled)
{
    return scaled ? ScaledDeltaTime() : UnscaledDeltaTime();
}

float Time::UnscaledDeltaTime()
{
    return s_deltaTime;
}

float Time::ScaledDeltaTime()
{
    return s_deltaTime * s_timeScale;
}

void Time::SetDeltaTime(float newValue)
{
    s_deltaTime = newValue;
}

}  // namespace red
