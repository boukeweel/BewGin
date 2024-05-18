#pragma once
#include <vector>

#include "GameObject.h"
#include "Singleton.h"

class GameData : public bew::Singleton<GameData>
{
public:

	void AddPlayer(bew::GameObject* player);
	std::vector<bew::GameObject*>* GetPlayers();

private:
	friend class Singleton<GameData>;
	GameData() = default;

	std::vector<bew::GameObject*> m_Players;
};

