#pragma once
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{
	class HealthTextObserver :
		public Observer
	{
	public:
		HealthTextObserver(TextComponent* pTextComponent);

		void Notify(GameEvents event, GameObject* gameObject) override;

		virtual ~HealthTextObserver() = default;
		HealthTextObserver(const HealthTextObserver& other) = delete;
		HealthTextObserver(HealthTextObserver&& other) = delete;
		HealthTextObserver& operator=(const HealthTextObserver& other) = delete;
		HealthTextObserver& operator=(HealthTextObserver&& other) = delete;

	private:
		TextComponent* m_TextComponent;
		std::string m_livesTxt;
	};
}


