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

		void Play(sound_id id, int volume) override;

		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) = delete;
	};
}


