#pragma once

#include "RedEngine/Utils/Types.hpp"

namespace red
{
struct SystemInfo
{
    uint32 pageSize;
};

const SystemInfo& InitSystemInfo();
[[nodiscard]] const SystemInfo& GetSystemInfo();
}