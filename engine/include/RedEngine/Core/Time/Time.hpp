#pragma once

namespace red
{
/// Class responsible of the engine time.
/// This is where you can have the delta time and the time scale
class Time
{
public:
    /// Get the engine time scale
    static double TimeScale();
    /// Set the engine time scale
    static void TimeScale(double newTimeScale);

    /// Get the last frame delta time
    /// Equivalent to UnscaledDeltaTime if scaled = false
    /// Equivalent to ScaledDeltaTime if scaled = true
    static double DeltaTime(bool scaled = false);
    static double UnscaledDeltaTime();
    static double ScaledDeltaTime();

    static void DeltaTime(double newValue);

private:
    Time() = default;

    static double s_timeScale;
    static double s_deltaTime;
};
}  // namespace red