#include "BeeEnemyComponent.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

BeeEnemyComponent::BeeEnemyComponent(bew::GameObject* pParentObject)
: EnemyComponent(pParentObject)
{
}

void BeeEnemyComponent::TakeDamages(bew::GameObject* pPlayer)
{
	auto health = GetParentObject()->GetComponent<HealthComponent>();

	health->TakeDammages(1);

	if (health->GetLives() == 0)
	{
		GetParentObject()->SetIsActive(false);

		pPlayer->GetComponent<ScoreComponent>()->AddScore(m_AmountPoints);
	}
}
