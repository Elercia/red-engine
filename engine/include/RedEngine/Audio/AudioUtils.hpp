#pragma once

#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/RedEngineBase.hpp"

#include <fmod_common.h>

namespace red
{
FORCEINLINE bool FmodCheck(FMOD_RESULT result, const char* errorMsg);

FORCEINLINE void ConvertRef(FMOD_VECTOR& out, const Vector2& vector);
FORCEINLINE void ConvertRef(Vector2& out, const FMOD_VECTOR& fmodVector);

FORCEINLINE FMOD_VECTOR Convert(const Vector2& vector);
FORCEINLINE Vector2 Convert(const FMOD_VECTOR& fmodVector);
}  // namespace red

#include "inl/AudioUtils.inl"