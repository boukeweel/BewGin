#include "LoggingSDLSoundSystem.h"

#include <iostream>

void bew::LoggingSDLSoundSystem::Play(sound_id id, float volume)
{
	//play sound function
	std::cout << "sound id " << id << " At volume " << volume;
}
