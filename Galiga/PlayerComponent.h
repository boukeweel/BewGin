#pragma once
#include <Component.h>
#include <vector>

class PlayerComponent :
    public bew::Component
{
public:
	PlayerComponent(bew::GameObject* pparentObject);

	void ResetPlayer();

	void FixedUpdate() override;
	void Update() override;

	bool GetAllowedToMove() const { return m_AllowedToMove; }

	void StartSuckUpAnimation(bew::GameObject* beam);

	virtual ~PlayerComponent() = default;
	PlayerComponent(const PlayerComponent& other) = delete;
	PlayerComponent(PlayerComponent&& other) = delete;
	PlayerComponent& operator=(const PlayerComponent& other) = delete;
	PlayerComponent& operator=(PlayerComponent&& other) = delete;
private:
	void GetEnemies();

	void PlayerGotHit();
	void CheckCollision();

	void constrainPlayerPosition();

	void SuckUpAnimation();

	void CreateExplosion();
	void SpawnExplosion();

	bool m_BeingSuckedUp{ false };
	bew::GameObject* m_pBeam;

	bool m_AllowedToMove{ true };
	bew::GameObject* m_pExplosion;

	std::vector<bew::GameObject*>* m_pEnemies;
};

