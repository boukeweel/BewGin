#pragma once
#include <vector>

#include "GameObject.h"
#include "Singleton.h"

//A book Keeping Class for all the entities in the games.
class GameEntityData : public bew::Singleton<GameEntityData>
{
public:

	void AddPlayer(bew::GameObject* player);
	std::vector<bew::GameObject*>* GetPlayers();

	void AddEnemy(bew::GameObject* enemy);
	void AddEnemies(std::vector<bew::GameObject*> enemies);
	std::vector<bew::GameObject*>* GetEnemies();

	void AddExplosion(bew::GameObject* explosion);
	bew::GameObject* GetExplosion() const;
	

	void ResetAll()
	{
		m_Players.clear();
		m_Enemies.clear();
		m_Explosion.clear();
	}

private:
	friend class Singleton<GameEntityData>;
	GameEntityData() = default;

	std::vector<bew::GameObject*> m_Players;
	std::vector<bew::GameObject*> m_Enemies;
	std::vector<bew::GameObject*> m_Explosion;
};

