#include "ScoreTextObserver.h"

#include "GameObject.h"
#include "LivesDisplayObserver.h"
#include "ScoreComponent.h"

ScoreTextObserver::ScoreTextObserver(bew::TextComponent* pTextComponent) : m_TextComponent{ pTextComponent }
{
	//to set the first base text
	m_ScoreTxt = m_TextComponent->getText();
	//still feels not good but bit better
	m_TextComponent->SetText(m_ScoreTxt + "0");
}

void ScoreTextObserver::Notify(bew::GameEvents event, bew::GameObject* gameObject)
{
	switch (event)
	{
	case bew::GameEvents::PlayerAddedScore:
		if (gameObject->HasComponent<ScoreComponent>())
		{
			int score = gameObject->GetComponent<ScoreComponent>()->getScore();

			m_TextComponent->SetText(m_ScoreTxt + std::to_string(score));
			
		}
		break;
	}

}