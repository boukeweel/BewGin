#include "GameData.h"

void GameData::AddPlayer(bew::GameObject* player) 
{
	m_Players.emplace_back(player);
}

std::vector<bew::GameObject*>* GameData::GetPlayers() 
{
	return &m_Players;
}
