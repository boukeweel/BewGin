#include "SwitchLevelSceneCommands.h"

#include "EnemySpawnerComponent.h"
#include "SceneManager.h"


NextWave::NextWave(bew::GameObject* pTargetObject) : m_pTargetObject{pTargetObject}
{}

void NextWave::Execute()
{
	m_pTargetObject->GetComponent<EnemySpawnerComponent>()->NextLevel();
}

void NextScene::Execute()
{
	int currentScene = static_cast<int>(bew::SceneManager::GetInstance().GetCurrentSceneId());
	bew::SceneManager::GetInstance().SwitchScene(currentScene + 1);
}