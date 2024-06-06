#pragma once
#include <Component.h>
#include <vector>

class PlayerComponent :
    public bew::Component
{
public:
	PlayerComponent(bew::GameObject* pparentObject);

	void FixedUpdate() override;

	virtual ~PlayerComponent() = default;
	PlayerComponent(const PlayerComponent& other) = delete;
	PlayerComponent(PlayerComponent&& other) = delete;
	PlayerComponent& operator=(const PlayerComponent& other) = delete;
	PlayerComponent& operator=(PlayerComponent&& other) = delete;
private:

	void CheckCollision();
	void constrainPlayerPosition();

	void GetEnemies();


	std::vector<bew::GameObject*>* m_pEnemies;
};

