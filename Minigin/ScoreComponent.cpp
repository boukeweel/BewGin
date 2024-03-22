#include "ScoreComponent.h"

#include "GameObject.h"

dae::ScoreComponent::ScoreComponent(GameObject* pparentObject) : Component(pparentObject)
{
}


void dae::ScoreComponent::Won()
{
	GetParentObject()->GetSubject()->notify(GameEvents::PlayerWon, GetParentObject());
}

void dae::ScoreComponent::AddScore(int addAmount)
{
	m_Score += addAmount;
	if (m_Score >= m_WinAmount)
		Won();

	GetParentObject()->GetSubject()->notify(GameEvents::PlayerAddedScore, GetParentObject());
}
