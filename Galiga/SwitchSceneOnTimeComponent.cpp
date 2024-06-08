#include "SwitchSceneOnTimeComponent.h"

#include "GameData.h"
#include "GameTime.h"
#include "SceneManager.h"

SwitchSceneOnTimeComponent::SwitchSceneOnTimeComponent(bew::GameObject* pParentOjbect, int Scene) : SwitchSceneOnTimeComponent(pParentOjbect,Scene,10)
{}

SwitchSceneOnTimeComponent::SwitchSceneOnTimeComponent(bew::GameObject* pParentOjbect, int Scene, float Time) : Component(pParentOjbect),m_TimeActive(Time),m_Timer{0},m_TargetScene{Scene}
{}


void SwitchSceneOnTimeComponent::Update()
{
	if(!m_Start)
		return;

	m_Timer += bew::GameTime::GetDeltaTimeFloat();
	if(m_Timer >= m_TimeActive)
	{
		bew::SceneManager::GetInstance().SwitchScene(m_TargetScene);
	}
}

void SwitchSceneOnTimeComponent::StartTwoPlayers()
{
	m_AmountCalled++;
	int amountNeeded = 1;
	if (GameData::GetInstance().GetTwoPlayers())
		amountNeeded = 2;

	if (m_AmountCalled == amountNeeded)
		StartTimer();
}
