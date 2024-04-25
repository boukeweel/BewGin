#pragma once
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>
#include <vector>

#include "AudioClip.h"

namespace bew
{
	using sound_id = unsigned short;
	class SoundSystem
	{
	public:
		SoundSystem();
		virtual ~SoundSystem();
		virtual void Play(sound_id id, int volume);

		void AddClip(sound_id id, std::unique_ptr<AudioClip> clip);
		void RemoveClip(sound_id id);

		AudioClip* GetAudioClip(sound_id id);
	protected:
		virtual void Run() {
			while (m_Running) {
				std::unique_lock<std::mutex> lock(m_QueueMutex);
				m_QueueCondition.wait(lock, [this] { return !m_EventQueue.empty(); });

				if (!m_EventQueue.empty()) {
					auto& event = m_EventQueue.front();
					m_EventQueue.pop();
					lock.unlock();

					AudioClip* clip = GetAudioClip(event.id);
					if (clip) {
						clip->Play(event.volume);
					}
				}
			}
		}
		std::mutex m_QueueMutex;
		std::condition_variable m_QueueCondition;

	private:
		std::unordered_map<sound_id, std::unique_ptr<AudioClip>> m_AudioClips;

		struct SoundEvent {
			sound_id id;
			int volume;
		};

		std::queue<SoundEvent> m_EventQueue;
		bool m_Running = true;
		std::thread m_WorkerThread;
	};
}


