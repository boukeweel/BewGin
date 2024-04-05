#include "ScoreComponent.h"

#include "GameObject.h"

dae::ScoreComponent::ScoreComponent(GameObject* pparentObject) : Component(pparentObject)
{
}


void dae::ScoreComponent::Won()
{
	GetParentObject()->GetSubject()->notify(GameEvents::PlayerWon, GetParentObject());
	m_Won = true;
}

void dae::ScoreComponent::AddScore(int addAmount)
{
	if(m_Won != true)
	{
		m_Score += addAmount;
		GetParentObject()->GetSubject()->notify(GameEvents::PlayerAddedScore, GetParentObject());
		if (m_Score >= m_WinAmount)
			Won();
	}
}
