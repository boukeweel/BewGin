#pragma once
#include "SoundSystem.h"

namespace bew
{
	class SDLSoundSystem :
		public SoundSystem
	{
	public:
		SDLSoundSystem() = default;
		virtual ~SDLSoundSystem() = default;
		/*void Play(sound_id id, float volume) override;*/
	};
}


