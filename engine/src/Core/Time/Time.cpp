#include <RedEngine/Core/Time/Time.hpp>
#include <RedEngine/Math/Math.hpp>

namespace red
{
double Time::s_timeScale = 1.F;
double Time::s_deltaTime = 0.F;

double Time::TimeScale() { return s_timeScale; }

void Time::TimeScale(double newTimeScale) { s_timeScale = Mathf::Clamp01(newTimeScale); }

double Time::DeltaTime(bool scaled) { return scaled ? ScaledDeltaTime() : UnscaledDeltaTime(); }

double Time::UnscaledDeltaTime() { return s_deltaTime; }

double Time::ScaledDeltaTime() { return s_deltaTime * s_timeScale; }

void Time::DeltaTime(double newValue) { s_deltaTime = newValue; }

}  // namespace red
