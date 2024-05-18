#include "BossEnemyComponent.h"

#include "AnimatorComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "SpriteSheetComponent.h"

BossEnemyComponent::BossEnemyComponent(bew::GameObject* pParentObject) : EnemyComponent(pParentObject)
{
}

void BossEnemyComponent::TakeDamages(bew::GameObject* pPlayer)
{
	auto health = GetParentObject()->GetComponent<HealthComponent>();

	health->TakeDammages(1);

	GetParentObject()->GetComponent<bew::SpriteSheetComponent>()->SetSprite(1, 0);
	GetParentObject()->GetComponent<bew::AnimatorComponent>()->SwitchAnimation(1 ,true);

	if (health->GetLives() == 0)
	{
		GetParentObject()->SetIsActive(false);

		pPlayer->GetComponent<ScoreComponent>()->AddScore(m_AmountPoints);
	}
}
