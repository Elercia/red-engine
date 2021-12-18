#pragma once

#include "RedEngine/Audio/AudioModule.hpp"
#include "RedEngine/Math/Vector.hpp"


#include <fmod_common.h>

namespace red
{
struct FmodUtils
{
    static bool FmodCheck(FMOD_RESULT result, const char* errorMsg);

    static void ConvertRef(FMOD_VECTOR& out, const Vector2& vector);
    static void ConvertRef(Vector2& out, const FMOD_VECTOR& fmodVector);

    static FMOD_VECTOR Convert(const Vector2& vector);
    static Vector2 Convert(const FMOD_VECTOR& fmodVector);
};

}  // namespace red