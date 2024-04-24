#include "SoundSystem.h"

void bew::SoundSystem::AddClip(sound_id id, std::unique_ptr<AudioClip> clip)
{
	m_AudioClips[id] = std::move(clip);
}

void bew::SoundSystem::RemoveClip(sound_id id)
{
	m_AudioClips.erase(id);
}

bew::AudioClip* bew::SoundSystem::GetAudioClip(sound_id id)
{
	return nullptr;
}
