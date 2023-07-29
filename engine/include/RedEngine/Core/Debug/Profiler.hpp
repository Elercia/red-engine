#pragma once

#if defined(RED_USE_PROFILER)

#ifdef None
#undef None  // seems to be define inside X11
#endif

#include <optick.h>

struct ProfilerCategory
{
    static inline auto Rendering = Optick::Category::Rendering;
    static inline auto Physics = Optick::Category::Physics;
    static inline auto Input = Optick::Category::Input;
    static inline auto Debug = Optick::Category::Input;
    static inline auto None = Optick::Category::Input;
};

#define PROFILER_GENERATE_APP_PROFILE(...) OPTICK_APP(#__VA_ARGS__)
#define PROFILER_SHUTDOWN()                OPTICK_SHUTDOWN()
#define PROFILER_FRAME(...)                OPTICK_FRAME(#__VA_ARGS__)
#define PROFILER_EVENT(...)                OPTICK_EVENT(#__VA_ARGS__)
#define PROFILER_EVENT_CATEGORY(MSG, CAT)  OPTICK_CATEGORY(MSG, CAT)
#define PROFILER_THREAD(...)               OPTICK_START_THREAD(__VA_ARGS__)

#else

enum class ProfilerCategory
{
    Rendering,
    Physics,
    Input,
    Debug,
    None
};

#define PROFILER_GENERATE_APP_PROFILE(...)
#define PROFILER_SHUTDOWN(...)
#define PROFILER_FRAME(...)
#define PROFILER_EVENT(...)
#define PROFILER_EVENT_CATEGORY(...)
#define PROFILER_THREAD(...)

#endif