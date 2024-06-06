#include "EnemyAttackControllerComponent.h"

#include "EnemyComponent.h"
#include "EnemySpawnerComponent.h"
#include "GameEntityData.h"
#include "GameTime.h"
#include "PoolComponent.h"
#include "RandomFunctions.h"
#include "SubjectComponent.h"

EnemyAttackControllerComponent::EnemyAttackControllerComponent(bew::GameObject* pParentObject) : Component(pParentObject)
{
	m_pEnemies = GameEntityData::GetInstance().GetEnemies();
}

void EnemyAttackControllerComponent::Update()
{
	
	EnemyAttacking();
	DisabledTime();
	CheckAllEnemiesDead();
}

void EnemyAttackControllerComponent::EnemyAttacking()
{
	if (!m_pEnemies || m_pEnemies->empty() || m_StartDisabledTimer) {
		return;
	}

	if (GetParentObject()->GetComponent<FormationComponent>()->GetIsLocked())
	{
		m_Timer += bew::GameTime::GetDeltaTimeFloat();

		if (m_Timer >= m_EnemyAttackDelay)
		{
			m_Timer -= m_EnemyAttackDelay;

			bew::GameObject* selectEnemy = SelectRandomEnemy();
			if (selectEnemy)
				selectEnemy->GetComponent<EnemyComponent>()->SetAbleToAttack(true);
		}
	}
}

void EnemyAttackControllerComponent::DisabledTime()
{
	//lol ofc this does not work object is not active XD
	if (m_StartDisabledTimer)
	{
		m_DisabledTimer += bew::GameTime::GetDeltaTimeFloat();

		if (m_DisabledTimer >= m_DisabledTime)
		{
			GetParentObject()->GetComponent<bew::SubjectComponent>()->GetSubject()->notify(bew::GameEvents::UnPauseEnemyAttacking, GetParentObject());
			m_DisabledTimer = 0;
			m_StartDisabledTimer = false;
		}
	}
}

void EnemyAttackControllerComponent::CheckAllEnemiesDead() const
{
	bool allDead = true;
	for (const auto enemy : *m_pEnemies)
	{
		if(enemy->GetComponent<PoolComponent>()->InUse())
		{
			allDead = false;
			break;
		}
	}

	if(allDead)
	{
		GetParentObject()->GetComponent<EnemySpawnerComponent>()->NextLevel();
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

