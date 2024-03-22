#include "TempComands.h"

#include "GameObject.h"
#include "HealthComponent.h"

dae::DammagesPlayer::DammagesPlayer(GameObject* targetObject, int Dammages) : m_TargetObject{ targetObject }, m_Damages{ Dammages }
{
	
}


void dae::DammagesPlayer::Execute()
{
	if(m_TargetObject->HasComponent<HealthComponent>())
		m_TargetObject->GetComponent<HealthComponent>()->TakeDammages(m_Damages);
	
}
