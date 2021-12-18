#pragma once



#ifdef RED_USE_PROFILER

#include <optick.h>

#define PROFILER_APP(...) OPTICK_APP(__VA_ARGS__)
#define PROFILER_SHUTDOWN(...) OPTICK_SHUTDOWN(__VA_ARGS__)
#define PROFILER_FRAME(...) OPTICK_FRAME(__VA_ARGS__)
#define PROFILER_CATEGORY(CAT, COLOR) OPTICK_CATEGORY(CAT, COLOR)

#else

#define PROFILER_APP(...)
#define PROFILER_SHUTDOWN(...)
#define PROFILER_FRAME(...)
#define PROFILER_CATEGORY(...)

#endif