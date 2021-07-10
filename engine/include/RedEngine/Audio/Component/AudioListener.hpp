#pragma once

#include "fmod_common.h"

#include "RedEngine/Core/Components/Component.hpp"
#include "RedEngine/Math/Vector.hpp"

namespace red
{
class AudioListener : public Component
{
    friend class AudioSystem;

public:
    AudioListener(Entity* owner);
    ~AudioListener();

private:
    int m_listenerId;
    Vector2 m_lastFramePos;
};

}  // namespace red