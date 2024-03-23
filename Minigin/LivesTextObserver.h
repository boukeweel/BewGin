#pragma once
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{
	class LivesTextObserver :
		public Observer
	{
	public:
		LivesTextObserver(TextComponent* pTextComponent);

		void Notify(GameEvents event, GameObject* gameObject) override;

		virtual ~LivesTextObserver() = default;
		LivesTextObserver(const LivesTextObserver& other) = delete;
		LivesTextObserver(LivesTextObserver&& other) = delete;
		LivesTextObserver& operator=(const LivesTextObserver& other) = delete;
		LivesTextObserver& operator=(LivesTextObserver&& other) = delete;

	private:
		TextComponent* m_TextComponent;
		std::string m_livesTxt;
	};
}


