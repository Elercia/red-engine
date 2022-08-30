#include "RedEngine/Utils/SystemInfo.hpp"

#ifdef RED_WINDOWS
#include <sysinfoapi.h>
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
