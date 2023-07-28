#pragma once

#include <debugbreak.h>
#include <fmt/format.h>
#include "RedEngine/Core/Container/String.hpp"

namespace red
{
void LogAssert(const char* filename, int line, const String& s);

template <typename... Args>
bool HandleAssert(bool expr, StringView exprStr, const char* filename, int line, const String& message = "",
                  Args... args)
{
    if (expr)
        return false;

    String logString = fmt::format("Assertion failed {}", exprStr);

    if (!message.empty())
    {
        logString = fmt::format("{} : {}", logString, message, std::forward<Args>(args)...);
    }

    LogAssert(filename, line, logString);

#ifdef RED_BREAK_ON_ASSERT
    return true;
#else
    return false;
#endif
}
}  // namespace red

#ifdef RED_DEBUG

// TODO Add a abort reason (out of memory for exemple)
#define RedAbort(...)                                                             \
    do                                                                            \
    {                                                                             \
        if (red::HandleAssert(false, "abort", __FILE__, __LINE__, ##__VA_ARGS__)) \
            debug_break();                                                        \
        std::abort();                                                             \
    } while (0);

#define RedAssert(expr, ...)                                                   \
    do                                                                         \
    {                                                                          \
        if (red::HandleAssert(expr, #expr, __FILE__, __LINE__, ##__VA_ARGS__)) \
            debug_break();                                                     \
    } while (0);

#else

#define RedAbort(...) abort();
#define RedAssert(expr, ...)

#endif  // RED_DEBUG

#define RedError(...)            RedAssert(false, ##__VA_ARGS__)
#define RedAssertNotReached(...) RedAssert(false, ##__VA_ARGS__)

#define CheckReturn(EXPR)      \
    {                          \
        auto exprValue = EXPR; \
        if (!exprValue)        \
            return exprValue;  \
    }
