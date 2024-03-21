#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* pparentObject) : Component(pparentObject)
{
}


void dae::ScoreComponent::Won()
{
	//todo notify observer
}

void dae::ScoreComponent::AddScore(int addAmount)
{
	m_Score += addAmount;
	if (m_Score >= m_WinAmount)
		Won();

	//todo notify teks component
}
