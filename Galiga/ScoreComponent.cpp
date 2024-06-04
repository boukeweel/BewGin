#include "ScoreComponent.h"

#include "GameObject.h"
#include "SubjectComponent.h"

ScoreComponent::ScoreComponent(bew::GameObject* pparentObject) : Component(pparentObject)
{
}

//this can be done better maybe in diffrent class that the components that need it can inherit from
//todo ^
void ScoreComponent::notifySubject(bew::GameEvents event, bew::GameObject* object)
{
	object->GetComponent<bew::SubjectComponent>()->GetSubject()->notify(event, object);
}


void ScoreComponent::AddScore(int addAmount)
{
	if(m_Won != true)
	{
		m_Score += addAmount;
		notifySubject(bew::GameEvents::PlayerAddedScore, GetParentObject());
	}
}
