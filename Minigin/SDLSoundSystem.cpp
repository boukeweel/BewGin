#include "SDLSoundSystem.h"

void bew::SDLSoundSystem::Play(sound_id id, int volume)
{
	std::lock_guard<std::mutex> lock(m_QueueMutex);
	m_EventQueue.push({ id, volume });
	m_QueueCondition.notify_one();
}
