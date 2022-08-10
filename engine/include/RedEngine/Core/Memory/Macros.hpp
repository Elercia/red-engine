#pragma once

namespace red
{
#define RED_SAFE_DELETE(PTR) \
    if (PTR != nullptr)      \
    {                        \
        delete PTR;          \
        PTR = nullptr;       \
    }

#define RED_SAFE_FREE(PTR) \
    if (PTR != nullptr)    \
    {                      \
        std::free(PTR);    \
        PTR = nullptr;     \
    }
}  // namespace red
