#include "RedEngine/Core/Debug/DebugMacros.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"

namespace red
{
void LogAssert(const char* filename, int line, const String& s)
{
    GetRedLogger()->LogInternal(LogLevel::LEVEL_ERROR, line, filename, s);
}
}  // namespace red