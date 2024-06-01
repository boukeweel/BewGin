#pragma once
#include <vector>

#include "GameObject.h"
#include "Singleton.h"

//A book Keeping Class so that you dont need to pass everything to each other
class GameData : public bew::Singleton<GameData>
{
public:

	void AddPlayer(bew::GameObject* player);
	std::vector<bew::GameObject*>* GetPlayers();

	void AddEnemy(bew::GameObject* enemy);
	void AddEnemies(std::vector<bew::GameObject*> enemies);
	std::vector<bew::GameObject*>* GetEnemies();

private:
	friend class Singleton<GameData>;
	GameData() = default;

	std::vector<bew::GameObject*> m_Players;
	std::vector<bew::GameObject*> m_Enemies;
};

