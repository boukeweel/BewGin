#include "GameData.h"

void GameData::AddPlayer(bew::GameObject* player) 
{
	m_Players.emplace_back(player);
}

std::vector<bew::GameObject*>* GameData::GetPlayers() 
{
	return &m_Players;
}

void GameData::AddEnemy(bew::GameObject* enemy)
{
	m_Enemies.emplace_back(enemy);
}

void GameData::AddEnemies(std::vector<bew::GameObject*> enemies)
{
	m_Enemies.reserve(m_Enemies.size() + enemies.size());
	m_Enemies.insert(m_Enemies.end(), enemies.begin(), enemies.end());
}

std::vector<bew::GameObject*>* GameData::GetEnemies()
{
	return &m_Enemies;
}

