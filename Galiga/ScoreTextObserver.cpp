#include "ScoreTextObserver.h"

#include "GameObject.h"
#include "LivesDisplayObserver.h"
#include "ScoreComponent.h"

ScoreTextObserver::ScoreTextObserver(bew::TextComponent* pTextComponent) : m_pTextComponent{ pTextComponent }
{
	m_ScoreTxt = m_pTextComponent->getText();
	m_pTextComponent->SetText(m_ScoreTxt + "0");
}

void ScoreTextObserver::Notify(bew::GameEvents event, bew::GameObject* gameObject)
{
	if(event == bew::GameEvents::PlayerAddedScore)
	{
		if (gameObject->HasComponent<ScoreComponent>())
		{
			int score = gameObject->GetComponent<ScoreComponent>()->getScore();

			m_pTextComponent->SetText(m_ScoreTxt + std::to_string(score));
		}
	}
}