#pragma once

#ifdef RED_USE_PROFILER

#include <optick.h>

struct ProfilerCategory
{
    static inline Optick::Category::Type Rendering = Optick::Category::Rendering;
    static inline Optick::Category::Type Input = Optick::Category::Input;
    static inline Optick::Category::Type Debug = Optick::Category::Input;
    static inline Optick::Category::Type None = Optick::Category::Input;
};

#define PROFILER_GENERATE_APP_PROFILE(...) OPTICK_APP(__VA_ARGS__)
#define PROFILER_SHUTDOWN(...)             OPTICK_SHUTDOWN(__VA_ARGS__)
#define PROFILER_FRAME(...)                OPTICK_FRAME(__VA_ARGS__)
#define PROFILER_EVENT(...)                OPTICK_EVENT(__VA_ARGS__)
#define PROFILER_EVENT_CATEGORY(MSG, CAT)  OPTICK_CATEGORY(MSG, CAT)
#define PROFILER_THREAD(...)               OPTICK_THREAD(__VA_ARGS__)

#else

struct ProfilerCategory
{
    enum Enum
    {
        Rendering,
        Input,
        Debug,
        None
    };
};

#define PROFILER_GENERATE_APP_PROFILE(...)
#define PROFILER_SHUTDOWN(...)
#define PROFILER_FRAME(...)
#define PROFILER_EVENT(...)
#define PROFILER_EVENT_CATEGORY(...)
#define PROFILER_THREAD(...)

#endif