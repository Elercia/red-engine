#pragma once

#include <debugbreak.h>
#include <fmt/format.h>
#include <string>

namespace red
{
void LogAssert(const char* filename, int line, const std::string& s);

template <typename... Args>
bool HandleAssert(bool expr, const char* filename, int line, const std::string& message = "", Args... args)
{
    if (expr)
        return false;

    std::string logString = fmt::format(message, std::forward<Args>(args)...);

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
#define RedAbort(...)                                                    \
    do                                                                   \
    {                                                                    \
        if (red::HandleAssert(false, __FILE__, __LINE__, ##__VA_ARGS__)) \
            debug_break();                                               \
        std::abort();                                                    \
    } while (0);

#define RedAssert(expr, ...)                                            \
    do                                                                  \
    {                                                                   \
        if (red::HandleAssert(expr, __FILE__, __LINE__, ##__VA_ARGS__)) \
            debug_break();                                              \
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
