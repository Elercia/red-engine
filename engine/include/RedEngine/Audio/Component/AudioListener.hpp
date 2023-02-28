#pragma once

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Math/Vector.hpp"

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
    int m_listenerId;
    Vector2 m_lastFramePos;
};

}  // namespace red