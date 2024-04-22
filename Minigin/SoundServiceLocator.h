#pragma once
#include <memory>

#include "SoundSystem.h"

namespace bew
{
	class SoundServiceLocator final
	{
		static std::unique_ptr<SoundSystem> SoundSystem_Instance;
	public:
		static SoundSystem& GetSoundSystem() { return *SoundSystem_Instance; }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem) { SoundSystem_Instance = std::move(soundSystem); }
	};
}


