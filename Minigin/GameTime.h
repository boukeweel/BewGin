#pragma once
#include <chrono>
#include <thread>

namespace bew
{
	class GameTime final
	{
		friend class BewGin;

	public:
		[[nodiscard]] static double GetDeltaTime() { return s_DeltaTime; }
		[[nodiscard]] static float GetDeltaTimeFloat() { return static_cast<float>(s_DeltaTime); }

		[[nodiscard]] static double GetFixedDeltaTime() { return s_FixedDeltaTime; }
		
	private:

		static void Update();
		static void SetmaxFps(const int& maxFrames) { s_MaxFrames = maxFrames; }

		static std::chrono::milliseconds GetSleepTime()
		{
			const auto ms_per_frame = std::chrono::milliseconds(1000 / s_MaxFrames);
			const auto frame_start_time = std::chrono::steady_clock::now();
			const auto frame_end_time = frame_start_time + ms_per_frame;
			return std::chrono::duration_cast<std::chrono::milliseconds>(frame_end_time - frame_start_time);
		}

		inline static double s_FixedDeltaTime{ 1.0 / 60.0 };
		inline static double s_MaxDeltatTime{ 1.0 / 30 };

		inline static int s_MaxFrames{ 60 };
		inline static double s_DeltaTime;
		inline static std::chrono::time_point<std::chrono::high_resolution_clock> s_LastTime{ std::chrono::high_resolution_clock::now() };
		inline static std::chrono::time_point<std::chrono::high_resolution_clock> s_CurrentTime{ std::chrono::high_resolution_clock::now() };
	};
}


