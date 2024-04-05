#include "ScoreComponent.h"

#include "GameObject.h"
#include "SubjectComponent.h"

bew::ScoreComponent::ScoreComponent(GameObject* pparentObject) : Component(pparentObject)
{
}

//this can be done better maybe in diffrent class that the components that need it can inherit from
//todo ^
void bew::ScoreComponent::notifySubject(GameEvents event, GameObject* object)
{
	object->GetComponent<SubjectComponent>()->GetSubject()->notify(event, object);
}

void bew::ScoreComponent::Won()
{
	notifySubject(GameEvents::PlayerWon, GetParentObject());
	m_Won = true;
}

void bew::ScoreComponent::AddScore(int addAmount)
{
	if(m_Won != true)
	{
		m_Score += addAmount;
		notifySubject(GameEvents::PlayerAddedScore, GetParentObject());
		if (m_Score >= m_WinAmount)
			Won();
	}
}
