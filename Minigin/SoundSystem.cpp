#include "SoundSystem.h"

#include <iostream>
#include <ostream>

bew::SoundSystem::SoundSystem()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cerr << "SDL Mixer initialization error: " << Mix_GetError() << std::endl;
	}
	m_WorkerThread = std::thread(&SoundSystem::Run, this);
}

bew::SoundSystem::~SoundSystem()
{
	m_Running = false;
	m_QueueCondition.notify_one(); 
	if (m_WorkerThread.joinable()) {
		m_WorkerThread.join();
	}
}

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
	if (m_AudioClips.contains(id)) {
		return m_AudioClips[id].get();
	}
	return nullptr;
}
