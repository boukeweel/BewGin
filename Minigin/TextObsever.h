#pragma once
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{
	class TextObsever final:
		public Observer
	{
		TextObsever(TextComponent* textComponet,const std::string& baseText);
		void Notify(const GameEvents& event, GameObject* gameObject) override;

		virtual ~TextObsever() = default;
		TextObsever(const TextObsever& other) = delete;
		TextObsever(TextObsever&& other) = delete;
		TextObsever& operator=(const TextObsever& other) = delete;
		TextObsever& operator=(TextObsever&& other) = delete;
	private:
		TextComponent* m_TextCompoent;
		std::string m_BaseText;
	};
}


