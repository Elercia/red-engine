#pragma once

#include <debugbreak.h>
#include <string_view>

namespace red
{
enum class ErrorReturn
{
    BREAK,
    CONTINUE
};
ErrorReturn HandleAssert(bool expr, std::string_view message, const char* filename,
                         int line);  // TODO add the possibility to add arguments to the message (, ...)
}  // namespace red

#ifndef RED_RETAIL_MODE

// TODO Add a abort reason (out of memory for exemple)
#define RED_ABORT(MSG)                                                             \
    do                                                                             \
    {                                                                              \
        red::ErrorReturn _ret = red::HandleAssert(false, MSG, __FILE__, __LINE__); \
        if (_ret == red::ErrorReturn::BREAK)                                       \
            debug_break();                                                         \
    } while (0);

#define RED_ASSERT(expr, MSG)                                                     \
    do                                                                            \
    {                                                                             \
        red::ErrorReturn _ret = red::HandleAssert(expr, MSG, __FILE__, __LINE__); \
        if (_ret == red::ErrorReturn::BREAK)                                      \
            debug_break();                                                        \
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
#define RED_ASSERT_S(expr) RED_ASSERT(expr, "Assert triggered")

#define CheckReturn(EXPR)      \
    {                          \
        auto exprValue = EXPR; \
        if (!exprValue)        \
            return exprValue;  \
    }
