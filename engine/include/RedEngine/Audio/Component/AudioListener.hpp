#pragma once

#include "RedEngine/Core/Components/Component.hpp"
#include "fmod_common.h"

namespace red
{
class AudioListener : public Component
{
    friend class AudioSystem;

public:
    AudioListener(Entity* owner);
    ~AudioListener();

private:
    FMOD_VECTOR m_fmodVect;
    int m_listenerId;

    static int s_listenerId;
};

}  // namespace red