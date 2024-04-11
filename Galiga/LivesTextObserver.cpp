#include "LivesTextObserver.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

LivesTextObserver::LivesTextObserver(bew::TextComponent* pTextComponent) : m_TextComponent{pTextComponent}
{
	//to set the first base text
	m_livesTxt = m_TextComponent->getText();

	m_TextComponent->SetText(m_livesTxt + "3");
}

void LivesTextObserver::Notify(bew::GameEvents event, bew::GameObject* gameObject)
{
	switch (event)
	{
	case bew::GameEvents::PlayerTookDamages:
		if (gameObject->HasComponent<HealthComponent>())
		{
			int lives = gameObject->GetComponent<HealthComponent>()->GetLives();

			m_TextComponent->SetText(m_livesTxt + std::to_string(lives));
		}
		break;
	case bew::GameEvents::PlayerDied:
		m_TextComponent->SetText(m_livesTxt + "Dead");
		break;
	}

}
