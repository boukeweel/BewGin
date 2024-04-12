#include "TempComands.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "SceneManager.h"
#include "ScoreComponent.h"

DammagesPlayer::DammagesPlayer(bew::GameObject* targetObject, int Dammages) : m_TargetObject{ targetObject }, m_Damages{ Dammages }
{
}

void DammagesPlayer::Execute()
{
	if (!m_TargetObject->GetIsActive())
		return;

	if(m_TargetObject->HasComponent<HealthComponent>())
		m_TargetObject->GetComponent<HealthComponent>()->TakeDammages(m_Damages);
}

Score::Score(bew::GameObject* targetObject, int score) : m_TargetObject{ targetObject }, m_Score{ score }
{
}

void Score::Execute()
{
	if (!m_TargetObject->GetIsActive())
		return;

	if (m_TargetObject->HasComponent<ScoreComponent>())
		m_TargetObject->GetComponent<ScoreComponent>()->AddScore(100);
}

SwitchScene::SwitchScene(unsigned int scene) :m_Scene{scene}
{
}

void SwitchScene::Execute()
{
	bew::SceneManager::GetInstance().LoadScene(m_Scene);
}