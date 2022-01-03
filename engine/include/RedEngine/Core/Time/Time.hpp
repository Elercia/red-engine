#pragma once

namespace red
{
/// Class responsible of the engine time.
/// This is where you can have the delta time and the time scale
class Time
{
public:
    /// Get the engine time scale
    static float TimeScale();
    /// Set the engine time scale
    static void SetTimeScale(float newTimeScale);

    /// Get the last frame delta time
    /// Equivalent to UnscaledDeltaTime if scaled = false
    /// Equivalent to ScaledDeltaTime if scaled = true
    static float DeltaTime(bool scaled = true);
    static float UnscaledDeltaTime();
    static float ScaledDeltaTime();

    static void SetDeltaTime(float newValue);

private:
    Time() = default;

    static float s_timeScale;
    static float s_deltaTime;
};
}  // namespace red