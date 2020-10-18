#pragma once

namespace red
{
#define RED_SAFE_DELETE(PTR) \
    if (PTR)                 \
    {                        \
        delete PTR;          \
        PTR = nullptr;       \
    }  
}  // namespace red