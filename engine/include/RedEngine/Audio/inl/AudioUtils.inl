#include "fmod_errors.h"

namespace red
{
bool FmodCheck(FMOD_RESULT result, const char* errorMsg)
{
    bool ret = result == FMOD_OK;

    RED_ASSERT(ret, FMOD_ErrorString(result));

    return ret;
}

void ConvertRef(FMOD_VECTOR& out, const Vector2& vector)
{
    out.x = vector.x;
    out.y = vector.y;
    out.z = 1;
}

void ConvertRef(Vector2& out, const FMOD_VECTOR& fmodVector)
{
    out.x = fmodVector.x;
    out.x = fmodVector.x;
    out.y = fmodVector.y;
}

FMOD_VECTOR Convert(const Vector2& vector)
{
    FMOD_VECTOR fmodVec;
    ConvertRef(fmodVec, vector);
    return fmodVec;
}

Vector2 Convert(const FMOD_VECTOR& fmodVector)
{
    Vector2 vec;
    ConvertRef(vec, fmodVector);
    return vec;
}

}  // namespace red
