#include "SwitchSceneOnTimeComponent.h"

#include "GameTime.h"
#include "SceneManager.h"

SwitchSceneOnTimeComponent::SwitchSceneOnTimeComponent(bew::GameObject* pParentOjbect, int Scene) : SwitchSceneOnTimeComponent(pParentOjbect,Scene,10)
{}

SwitchSceneOnTimeComponent::SwitchSceneOnTimeComponent(bew::GameObject* pParentOjbect, int Scene, float Time) : Component(pParentOjbect),m_TimeActive(Time),m_Timer{0},m_TargetScene{Scene}
{}


void SwitchSceneOnTimeComponent::Update()
{
	m_Timer += bew::GameTime::GetDeltaTimeFloat();
	if(m_Timer >= m_TimeActive)
	{
		bew::SceneManager::GetInstance().SwitchScene(m_TargetScene);
	}
}
