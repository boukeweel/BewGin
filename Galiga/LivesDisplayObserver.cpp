#include "LivesDisplayObserver.h"

#include <iostream>

#include "GameData.h"
#include "GameEntityData.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "SceneManager.h"
#include "ScoreComponent.h"

LivesDisplayObserver::LivesDisplayObserver(PlayerHealthDisplayComponent* pDisplayComponent) : m_pDisplayHealth{ pDisplayComponent }
{
}

void LivesDisplayObserver::Notify(bew::GameEvents event, bew::GameObject*)
{
	switch (event)
	{
	case bew::GameEvents::TakeDamages:
		m_pDisplayHealth->RemoveHealthCount();
		break;
	case bew::GameEvents::ObjectDied:

		auto Players = GameEntityData::GetInstance().GetPlayers();
		bool allDead = true;

		//if its co-op wait till both are dead
		for (const auto& player : *Players)
		{
			if (player->GetComponent<HealthComponent>()->GetAlive())
			{
				allDead = false;
				break;
			}
		}
		if(allDead)
		{
			//add score's to GameData
			GameData::GetInstance().SetCurrentScoreP1((*Players)[0]->GetComponent<ScoreComponent>()->getScore());
			if(Players->size() == 2)
				GameData::GetInstance().SetCurrentScoreP2((*Players)[1]->GetComponent<ScoreComponent>()->getScore());
			bew::SceneManager::GetInstance().SwitchScene(2);
		}
		break;
	}

}
