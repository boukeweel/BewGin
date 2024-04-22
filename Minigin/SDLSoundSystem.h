#pragma once
#include "SoundSystem.h"

namespace bew
{
	class SDLSoundSystem :
		public SoundSystem
	{
		void Play(sound_id id, float volume) override;
	};
}


