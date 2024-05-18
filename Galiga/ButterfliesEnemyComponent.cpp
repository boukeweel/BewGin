#include "ButterfliesEnemyComponent.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

ButterfliesEnemyComponent::ButterfliesEnemyComponent(bew::GameObject* pParentObject) : EnemyComponent(pParentObject)
{}

void ButterfliesEnemyComponent::TakeDamages(bew::GameObject * pPlayer)
{
	auto health = GetParentObject()->GetComponent<HealthComponent>();

	health->TakeDammages(1);

	if (health->GetLives() == 0)
	{
		GetParentObject()->SetIsActive(false);

		pPlayer->GetComponent<ScoreComponent>()->AddScore(100);
	}

}
