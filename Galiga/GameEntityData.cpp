#include "GameEntityData.h"

#include "AnimatorComponent.h"

void GameEntityData::AddPlayer(bew::GameObject* player) 
{
	m_pPlayers.emplace_back(player);
}

std::vector<bew::GameObject*>* GameEntityData::GetPlayers() 
{
	return &m_pPlayers;
}

void GameEntityData::AddEnemy(bew::GameObject* enemy)
{
	m_pEnemies.emplace_back(enemy);
}

void GameEntityData::AddEnemies(std::vector<bew::GameObject*> enemies)
{
	m_pEnemies.reserve(m_pEnemies.size() + enemies.size());
	m_pEnemies.insert(m_pEnemies.end(), enemies.begin(), enemies.end());
}

std::vector<bew::GameObject*>* GameEntityData::GetEnemies()
{
	return &m_pEnemies;
}

void GameEntityData::AddExplosion(bew::GameObject* explosion)
{
	m_pExplosion.emplace_back(explosion);
}

bew::GameObject* GameEntityData::GetExplosion() const
{
	for (auto* gameObject : m_pExplosion)
	{
		if (!gameObject->GetComponent<bew::AnimatorComponent>()->getCurrentAnimation()->GetIsAnimation())
		{
			return gameObject;
		}
	}
	return nullptr;
}



