#include "GameEntityData.h"

void GameEntityData::AddPlayer(bew::GameObject* player) 
{
	m_Players.emplace_back(player);
}

std::vector<bew::GameObject*>* GameEntityData::GetPlayers() 
{
	return &m_Players;
}

void GameEntityData::AddEnemy(bew::GameObject* enemy)
{
	m_Enemies.emplace_back(enemy);
}

void GameEntityData::AddEnemies(std::vector<bew::GameObject*> enemies)
{
	m_Enemies.reserve(m_Enemies.size() + enemies.size());
	m_Enemies.insert(m_Enemies.end(), enemies.begin(), enemies.end());
}

std::vector<bew::GameObject*>* GameEntityData::GetEnemies()
{
	return &m_Enemies;
}

