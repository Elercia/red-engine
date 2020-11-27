#pragma once

#include <RedEngine/RedEngineBase.hpp>

namespace red
{
#ifdef __clang__
/*code specific to clang compiler*/
#define FORCEINLINE __attribute__((always_inline))
#elif __GNUC__
/*code for GNU C compiler */
#define FORCEINLINE __attribute__((always_inline))
#elif _MSC_VER
/*code specific to MSVC compiler*/
#define FORCEINLINE __forceinline
#else
#error Unrecognized compiler
#endif
}  // namespace red