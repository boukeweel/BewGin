#pragma once
#include "Component.h"


namespace bew
{
	enum class GameEvents;
}

class HealthComponent final :
	public bew::Component
{
public:
	void TakeDammages(int amount);
	void Died();

	int GetLives() const { return m_Lifes; }

	//this is for object pooling of the enemy
	void SetLifes(int amoutLives);
	void SetBackAlive();

	HealthComponent(bew::GameObject* pparentObject, int lives);
	virtual ~HealthComponent() = default;
	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) = delete;

	void notifySubject(bew::GameEvents event, bew::GameObject* object);
private:
	int m_Lifes;
	bool m_IsAlive{true};
};



