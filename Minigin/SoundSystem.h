#pragma once
#include <unordered_map>
#include <vector>

#include "AudioClip.h"

namespace bew
{
	using sound_id = unsigned short;
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(sound_id id, float volume) = 0;

		void AddClip(sound_id id, std::unique_ptr<AudioClip> clip);
		void RemoveClip(sound_id id);

		AudioClip* GetAudioClip(sound_id id);

	private:
		std::unordered_map<sound_id, std::unique_ptr<AudioClip>> m_AudioClips;
	};
}


