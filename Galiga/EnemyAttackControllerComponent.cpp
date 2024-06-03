#include "EnemyAttackControllerComponent.h"

#include "EnemyComponent.h"
#include "GameData.h"
#include "GameTime.h"
#include "RandomFunctions.h"

EnemyAttackControllerComponent::EnemyAttackControllerComponent(bew::GameObject* pParentObject) : Component(pParentObject)
{
	m_pEnemies = GameData::GetInstance().GetEnemies();
}

void EnemyAttackControllerComponent::Update()
{
	if (!m_pEnemies || m_pEnemies->empty()) {
		return; // No enemies to select from
	}

	if(GetParentObject()->GetComponent<FormationComponent>()->GetIsLocked())
	{
		m_Timer += bew::GameTime::GetDeltaTimeFloat();

		if (m_Timer >= m_EnemyAttackDelay)
		{
			m_Timer -= m_EnemyAttackDelay;

			SelectRandomEnemy()->GetComponent<EnemyComponent>()->SetAbleToAttack(true);
		}
	}
	
}

bew::GameObject* EnemyAttackControllerComponent::SelectRandomEnemy() const
{
	int enemyIndex;
	bew::GameObject* selectedEnemy;

	//I feel like this is not good
	do {
		enemyIndex = bew::RandomFunctions::RandomI(static_cast<int>(m_pEnemies->size()));
		selectedEnemy = (*m_pEnemies)[enemyIndex];
	} while (selectedEnemy->GetComponent<EnemyComponent>()->GetIsDiving() || !selectedEnemy->GetIsActive());

	return selectedEnemy;
}

