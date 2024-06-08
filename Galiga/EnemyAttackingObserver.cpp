#include "EnemyAttackingObserver.h"

#include "GameEntityData.h"
#include "PlayerComponent.h"

EnemyAttackingObserver::EnemyAttackingObserver(EnemyAttackControllerComponent* pAttackingController) : m_pAttackingController{pAttackingController}
{
}

void EnemyAttackingObserver::Notify(bew::GameEvents event, bew::GameObject*)
{
	auto Players = GameEntityData::GetInstance().GetPlayers();
	switch (event)
	{
	case bew::GameEvents::UnPauseEnemyAttacking:
		for (auto& player : *Players)
		{
			player->SetIsActive(true);
			player->GetComponent<PlayerComponent>()->ResetPlayer();
		}
		break;
	case bew::GameEvents::PauseEnemyAttacking:
		
		bool AllHit = true;

		for (const auto& player : *Players)
		{
			if (player->GetIsActive())
			{
				AllHit = false;
				break;
			}
		}
		if (AllHit)
		{
			m_pAttackingController->StartDisabledTime();
		}
		break;
	}
}
