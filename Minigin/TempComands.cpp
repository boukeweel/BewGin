#include "TempComands.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

bew::DammagesPlayer::DammagesPlayer(GameObject* targetObject, int Dammages) : m_TargetObject{ targetObject }, m_Damages{ Dammages }
{
	
}


void bew::DammagesPlayer::Execute()
{
	if(m_TargetObject->HasComponent<HealthComponent>())
		m_TargetObject->GetComponent<HealthComponent>()->TakeDammages(m_Damages);
	
}

bew::Score::Score(GameObject* targetObject, int score) : m_TargetObject{ targetObject }, m_Score{ score }
{
}

void bew::Score::Execute()
{
	if (m_TargetObject->HasComponent<ScoreComponent>())
		m_TargetObject->GetComponent<ScoreComponent>()->AddScore(100);
}
