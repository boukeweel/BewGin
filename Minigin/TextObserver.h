#pragma once
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{
	class TextObserver :
		public Observer
	{
	public:
		TextObserver(TextComponent* pTextComponent);

		void Notify(GameEvents event, GameObject* gameObject) override;

		virtual ~TextObserver() = default;
		TextObserver(const TextObserver& other) = delete;
		TextObserver(TextObserver&& other) = delete;
		TextObserver& operator=(const TextObserver& other) = delete;
		TextObserver& operator=(TextObserver&& other) = delete;

	private:
		TextComponent* m_TextComponent;
		std::string m_livesTxt;
	};
}


