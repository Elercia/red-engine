#include "RedEngine/Audio/AudioUtils.hpp"

#include "RedEngine/Audio/AudioModule.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"

#include "fmod_errors.h"

namespace red
{
bool FmodUtils::FmodCheck(FMOD_RESULT result, const char* errorMsg)
{
    bool ret = result == FMOD_OK;

    if (!ret)
    {
        RedError(FMOD_ErrorString(result));
        RED_LOG_ERROR("Fmod error : {} with error {}", errorMsg, FMOD_ErrorString(result));
    }

    return ret;
}

void FmodUtils::ConvertRef(FMOD_VECTOR& out, const Vector2& vector)
{
    out.x = vector.x;
    out.y = vector.y;
    out.z = 1;
}

void FmodUtils::ConvertRef(Vector2& out, const FMOD_VECTOR& fmodVector)
{
    out.x = fmodVector.x;
    out.x = fmodVector.x;
    out.y = fmodVector.y;
}

FMOD_VECTOR FmodUtils::Convert(const Vector2& vector)
{
    FMOD_VECTOR fmodVec;
    FmodUtils::ConvertRef(fmodVec, vector);
    return fmodVec;
}

Vector2 FmodUtils::Convert(const FMOD_VECTOR& fmodVector)
{
    Vector2 vec;
    FmodUtils::ConvertRef(vec, fmodVector);
    return vec;
}

}  // namespace red
