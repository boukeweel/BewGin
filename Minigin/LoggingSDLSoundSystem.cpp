#include "LoggingSDLSoundSystem.h"

#include <iostream>


void bew::LoggingSDLSoundSystem::Play(sound_id id, int volume)
{
	m_RealSoundSystem->Play(id,volume);
	std::cout << "Playing: " << id << " at volume " << volume << std::endl;
}

void bew::LoggingSDLSoundSystem::AddClip(sound_id id, std::unique_ptr<AudioClip> clip)
{
	m_RealSoundSystem->AddClip(id, std::move(clip));
	std::cout << "added clip at id " << id << std::endl;
}


