#include "RedEngine/Audio/Component/AudioSource.hpp"

#include "RedEngine/Audio/Resource/SoundResourceLoader.hpp"
#include "RedEngine/Core/Components/Component.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Resources/ResourceHolderComponent.hpp"

namespace red
{
AudioSource::AudioSource(Entity* owner, SoundDesc desc) : Component(owner), m_desc(desc), m_currentChannel(nullptr)
{
    m_sound = m_owner->GetWorld()
                  ->GetSingletonComponent<ResourceHolderComponent>()
                  ->GetResourceLoader<SoundResourceLoader>()
                  ->LoadResource(Path::Resource(desc.name));
}

void AudioSource::Play()
{
    m_needStart = true;
    m_needStop = false;
}

void AudioSource::Stop()
{
    m_needStart = false;
    m_needStop = true;
}

}  // namespace red
