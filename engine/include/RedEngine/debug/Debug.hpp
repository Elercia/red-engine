#pragma once
#include <cstdlib>
#include "DebugBreak.hpp"

#ifdef _DEBUG
#define RED_ABORT_IF(expr, MSG) \
    do                          \
    {                           \
        if (!(expr))            \
        {                       \
            debug_break();      \
        }                       \
    } while (0);

#define RED_ABORT(MSG) \
    do                 \
    {                  \
        debug_break(); \
    } while (0);

#define RED_ASSERT(expr, MSG) \
    do                        \
    {                         \
        if (!(expr))          \
        {                     \
            debug_break();    \
        }                     \
    } while (0);

#else
#define RED_ABORT_IF(expr, MSG) \
    do                          \
    {                           \
        if (!(expr))            \
        {                       \
            abort();            \
        }                       \
    } while (0);

#define RED_ABORT(MSG) \
    do                 \
    {                  \
        abort();       \
    } while (0);

#define RED_ASSERT(expr, MSG) \
    do                        \
    {                         \
        if (!(expr))          \
        {                     \
            abort();          \
        }                     \
    } while (0);

#endif  // DEBUG

#define RED_ERROR(MSG) RED_ASSERT(false, MSG)
