#include "TextObsever.h"

#include <iostream>

#include "GameObject.h"
#include "HealthComponent.h"

dae::TextObsever::TextObsever(TextComponent* textComponet, const std::string& baseText): m_TextCompoent{textComponet},m_BaseText{baseText}
{
}

void dae::TextObsever::Notify(const GameEvents& event, GameObject* gameObject)
{
	switch (event)
	{
	case GameEvents::PlayerTookDammags:
		if(gameObject->HasComponent<HealthComponent>())
		{
			int lives = gameObject->GetComponent<HealthComponent>()->GetLives();
			m_BaseText += std::to_string(lives);
			m_TextCompoent->SetText(m_BaseText);
		}
		break;
	default:
		std::cout << "Something whent wrong";
			break;
	}
}

