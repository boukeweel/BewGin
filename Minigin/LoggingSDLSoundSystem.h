#pragma once
#include "SoundSystem.h"

namespace bew
{
	class LoggingSDLSoundSystem final :
		public SoundSystem
	{
	public:
		LoggingSDLSoundSystem() = default;
		virtual ~LoggingSDLSoundSystem() = default;
		void Play(sound_id id, float volume) override;
	};
}


