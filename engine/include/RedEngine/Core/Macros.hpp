#pragma once

namespace red
{
#ifdef __clang__
/*code specific to clang compiler*/
#define RED_FORCEINLINE __attribute__((always_inline)) inline
#elif __GNUC__
/*code for GNU C compiler */
#define RED_FORCEINLINE __attribute__((always_inline)) inline
#elif _MSC_VER
/*code specific to MSVC compiler*/
#define RED_FORCEINLINE __forceinline inline
#else
#error Unrecognized compiler
#endif
}  // namespace red
