#pragma once

namespace red
{
#define RED_SAFE_DELETE(PTR) \
    if (PTR)                 \
    {                        \
        delete PTR;          \
        PTR = nullptr;       \
    }

#define RED_SAFE_FREE(PTR) \
    if (PTR)               \
    {                      \
        std::free(PTR);    \
        PTR = nullptr;     \
    }
}  // namespace red