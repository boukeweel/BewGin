#include "LivesTextObserver.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

dae::LivesTextObserver::LivesTextObserver(TextComponent* pTextComponent) : m_TextComponent{pTextComponent}
{
	//to set the first base text
	m_livesTxt = m_TextComponent->getText();
}

void dae::LivesTextObserver::Notify(GameEvents event, GameObject* gameObject)
{
	switch (event)
	{
	case GameEvents::PlayerTookDamages:
		if (gameObject->HasComponent<HealthComponent>())
		{
			int lives = gameObject->GetComponent<HealthComponent>()->GetLives();

			m_TextComponent->SetText(m_livesTxt + std::to_string(lives));
		}
		break;
	case GameEvents::PlayerDied:
		m_TextComponent->SetText(m_livesTxt + "Dead");
		break;
	}

}
