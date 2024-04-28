#pragma once
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>

#include "AudioClip.h"

namespace bew
{
	using sound_id = unsigned short;
	class SoundSystem
	{

	public:
		SoundSystem();
		virtual ~SoundSystem();
		virtual void Play(sound_id id, int volume) = 0;

		virtual void AddClip(sound_id id, std::unique_ptr<AudioClip> clip);
		virtual void RemoveClip(sound_id id);

		AudioClip* GetAudioClip(sound_id id);

		SoundSystem(const SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other) = delete;
		SoundSystem& operator=(const SoundSystem& other) = delete;
		SoundSystem& operator=(SoundSystem&& other) = delete;
	protected:
		virtual void Run() {
			while (m_Running) {
				std::unique_lock<std::mutex> lock(m_QueueMutex);
				m_QueueCondition.wait(lock, [this] { return !m_EventQueue.empty(); });

				if (!m_EventQueue.empty()) {
					SoundEvent event = m_EventQueue.front();
					m_EventQueue.pop();
					lock.unlock();

					auto* clip = GetAudioClip(event.id);
					if (clip) {
						clip->SetVolume(event.volume);
						clip->Play();
					}
				}
			}
		}

		struct SoundEvent {
			sound_id id;
			int volume;
		};

		std::mutex m_QueueMutex;
		std::condition_variable m_QueueCondition;
		std::queue<SoundEvent> m_EventQueue;

	private:
		std::unordered_map<sound_id, std::unique_ptr<AudioClip>> m_AudioClips;
		bool m_Running = true;
		std::thread m_WorkerThread;
	};
}


