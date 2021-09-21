#include "RedEngine/Audio/Component/AudioSource.hpp"

#include "RedEngine/Audio/Resource/SoundResourceLoader.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Resources/ResourceHolderComponent.hpp"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(AudioSource)

AudioSource::AudioSource(Entity* owner) : Component(owner), m_desc(), m_currentChannel(nullptr)
{

}

AudioSource::AudioSource(Entity* owner, const SoundDesc& desc) : Component(owner), m_desc(desc), m_currentChannel(nullptr)
{
    m_sound = m_owner->GetWorld()
                  ->GetWorldComponent<ResourceHolderComponent>()
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
