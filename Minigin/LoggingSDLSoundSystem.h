#pragma once
#include "SDLSoundSystem.h"

namespace bew
{
	class LoggingSDLSoundSystem final :
		public SDLSoundSystem
	{
		
	public:
		LoggingSDLSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem) : m_RealSoundSystem{std::move(soundSystem)}{}
		virtual ~LoggingSDLSoundSystem() = default;

		void Play(sound_id id, int volume) override;

		void AddClip(sound_id id, std::unique_ptr<AudioClip> clip) override;

		LoggingSDLSoundSystem(const LoggingSDLSoundSystem& other) = delete;
		LoggingSDLSoundSystem(LoggingSDLSoundSystem&& other) = delete;
		LoggingSDLSoundSystem& operator=(const LoggingSDLSoundSystem& other) = delete;
		LoggingSDLSoundSystem& operator=(LoggingSDLSoundSystem&& other) = delete;

	private:
		std::unique_ptr<SoundSystem> m_RealSoundSystem;
	};
}


