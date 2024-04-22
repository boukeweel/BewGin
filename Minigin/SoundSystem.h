#pragma once
namespace bew
{
	using sound_id = unsigned short;
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(sound_id id, float volume) = 0;
	};
}


