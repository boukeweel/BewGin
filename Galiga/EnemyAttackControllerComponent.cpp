#include "EnemyAttackControllerComponent.h"

#include "EnemyComponent.h"
#include "GameEntityData.h"
#include "GameTime.h"
#include "RandomFunctions.h"

EnemyAttackControllerComponent::EnemyAttackControllerComponent(bew::GameObject* pParentObject) : Component(pParentObject)
{
	m_pEnemies = GameEntityData::GetInstance().GetEnemies();
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

			bew::GameObject* selectEnemy = SelectRandomEnemy();
			if(selectEnemy)
				selectEnemy->GetComponent<EnemyComponent>()->SetAbleToAttack(true);
		}
	}
	
}

bew::GameObject* EnemyAttackControllerComponent::SelectRandomEnemy() const
{
	std::vector<bew::GameObject*> validEnemies;

	for (auto enemy : *m_pEnemies) {
		if (enemy->GetIsActive() && !enemy->GetComponent<EnemyComponent>()->GetIsDiving()) {
			validEnemies.push_back(enemy);
		}
	}

	if (validEnemies.empty()) {
		return nullptr;
	}
	int enemyIndex = bew::RandomFunctions::RandomI(static_cast<int>(validEnemies.size()));
	return validEnemies[enemyIndex];
}

