#include "TempComands.h"

#include "EnemyComponent.h"
#include "EnemySpawnerComponent.h"
#include "GameEntityData.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "SpriteSheetComponent.h"

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

Score::Score(bew::GameObject* targetObject, int score) : m_pTargetObject{ targetObject }, m_Score{ score }
{
}

void Score::Execute()
{
	if (!m_pTargetObject->GetIsActive())
		return;

	if (m_pTargetObject->HasComponent<ScoreComponent>())
		m_pTargetObject->GetComponent<ScoreComponent>()->AddScore(100);
}

SwitchScene::SwitchScene(unsigned int scene) :m_Scene{scene}
{
}

void SwitchScene::Execute()
{
	auto& sceneManger = bew::SceneManager::GetInstance();

	if (sceneManger.GetCurrentSceneId() != m_Scene)
	{
		sceneManger.LoadScene(m_Scene);
	}
}

void NextWave::Execute()
{
	m_pTargetObject->GetComponent<EnemySpawnerComponent>()->NextLevel();
	
}

NextWave::NextWave(bew::GameObject* test)
{
	m_pTargetObject = test;
}
