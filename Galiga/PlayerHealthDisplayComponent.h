#pragma once
#include <vector>

#include "Component.h"

class PlayerHealthDisplayComponent : public bew::Component
{
public:
	PlayerHealthDisplayComponent(bew::GameObject* pparentObject, int health, bool p2 = false);

	void RemoveHealthCount();
	void AddHealthCount();

	PlayerHealthDisplayComponent(const PlayerHealthDisplayComponent& other) = delete;
	PlayerHealthDisplayComponent(PlayerHealthDisplayComponent&& other) = delete;
	PlayerHealthDisplayComponent& operator=(const PlayerHealthDisplayComponent& other) = delete;
	PlayerHealthDisplayComponent& operator=(PlayerHealthDisplayComponent&& other) = delete;

private:
	std::vector<bew::GameObject*> m_DisplayObjects;
	int m_Health;
};

