#include "LivesDisplayObserver.h"

#include <iostream>

#include "GameEntityData.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "SceneManager.h"
#include "ScoreComponent.h"

LivesDisplayObserver::LivesDisplayObserver(PlayerHealthDisplayComponent* pDisplayComponent) : m_DisplayHealth{ pDisplayComponent }
{
}

void LivesDisplayObserver::Notify(bew::GameEvents event, bew::GameObject* )
{
	switch (event)
	{
	case bew::GameEvents::TakeDamages:
		m_DisplayHealth->RemoveHealthCount();
		break;
	case bew::GameEvents::ObjectDied:

		auto Players = GameEntityData::GetInstance().GetPlayers();
		bool allDead = true;

		for (const auto& player : *Players)
		{
			if (player->GetComponent<HealthComponent>()->GetAlive())
			{
				allDead = false;
				break;
			}
		}
		if(allDead)
			bew::SceneManager::GetInstance().SwitchScene(2);
		break;
	}

}
