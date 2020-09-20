#pragma once
#include <debugbreak.h>

#include <string_view>

namespace red
{
namespace ErrorReturn
{
    constexpr int BREAK = 0;
    constexpr int CONTINUE = 1;
}  // namespace ErrorReturn
int HandleAssert(bool expr, std::string_view message, const char* filename, int line); //TODO add the possibility to add arguments to the message (, ...) 
}  // namespace red

#ifndef RED_RETAIL_MODE

#define RED_ABORT(MSG)                                               \
    do                                                               \
    {                                                                \
        int ret = red::HandleAssert(false, MSG, __FILE__, __LINE__); \
        if (ret == red::ErrorReturn::BREAK)                          \
            debug_break();                                           \
    } while (0);

#define RED_ASSERT(expr, MSG)                                        \
    do                                                               \
    {                                                                \
        int ret = red::HandleAssert(false, MSG, __FILE__, __LINE__); \
        if (ret == red::ErrorReturn::BREAK)                          \
            debug_break();                                           \
    } while (0);

#else
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
