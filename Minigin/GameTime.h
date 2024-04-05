#pragma once
#include <chrono>

#include "Singleton.h"

namespace bew
{
	class GameTime final
	{
		friend class Minigin;

	public:
		static double GetDeltaTime() { return s_DeltaTime; }
		static float GetDeltaTimeFloat() { return static_cast<float>(s_DeltaTime); }
		
	private:

		static void Update();
		static void SetmaxFps(const int& maxFrames) { s_MaxFrames = maxFrames; }

		static std::chrono::milliseconds GetSleepTime()
		{
			const auto ms_per_frame = std::chrono::milliseconds(1000 / s_MaxFrames);
			return std::chrono::duration_cast<std::chrono::milliseconds>(s_CurrentTime + ms_per_frame - std::chrono::high_resolution_clock::now());
		}


		inline static int s_MaxFrames{ 60 };
		inline static double s_DeltaTime;
		inline static std::chrono::time_point<std::chrono::high_resolution_clock> s_LastTime{ std::chrono::high_resolution_clock::now() };
		inline static std::chrono::time_point<std::chrono::high_resolution_clock> s_CurrentTime{ std::chrono::high_resolution_clock::now() };
	};
}


