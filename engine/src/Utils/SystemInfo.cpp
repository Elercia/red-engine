#include "RedEngine/Utils/SystemInfo.hpp"

#ifdef RED_WINDOWS
#define NOMINMAX 1
#include <sysinfoapi.h>
#endif

#ifdef RED_LINUX
#include <unistd.h>
#endif

namespace red
{
static SystemInfo s_systemInfo;

const SystemInfo& InitSystemInfo()
{
#ifdef RED_WINDOWS
    SYSTEM_INFO nativeInfo;
    ::GetSystemInfo(&nativeInfo);

    s_systemInfo.pageSize = nativeInfo.dwPageSize;
#elif defined(RED_LINUX)
    s_systemInfo.pageSize = ::getpagesize();
#else
#error not implemented
#endif

    return s_systemInfo;
}

const SystemInfo& GetSystemInfo()
{
    return s_systemInfo;
}
}  // namespace red
