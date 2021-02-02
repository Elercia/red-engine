#pragma once

#include "fmod_common.h"

#include "RedEngine/Core/Components/Component.hpp"

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