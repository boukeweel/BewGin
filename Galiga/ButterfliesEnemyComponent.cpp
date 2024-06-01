#include "ButterfliesEnemyComponent.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

std::vector<std::vector<glm::vec2>> ButterfliesEnemyComponent::s_AttackingPaths;

void ButterfliesEnemyComponent::CreateAttackingPaths()
{
	
}


ButterfliesEnemyComponent::ButterfliesEnemyComponent(bew::GameObject* pParentObject) : EnemyComponent(pParentObject)
{
	SetEnemyType(EnemyTypes::Butterfly);
}

void ButterfliesEnemyComponent::TakeDamages(bew::GameObject * pPlayer)
{
	auto health = GetParentObject()->GetComponent<HealthComponent>();

	health->TakeDammages(1);

	if (health->GetLives() == 0)
	{
		GetParentObject()->SetIsActive(false);

		pPlayer->GetComponent<ScoreComponent>()->AddScore(m_AmountPoints);
	}

}
