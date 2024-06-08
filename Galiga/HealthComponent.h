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

	HealthComponent(bew::GameObject* pparentObject, int lives);

	void TakeDammages(int amount);
	void Died();

	int GetLives() const { return m_Lifes; }
	bool GetAlive() const { return m_IsAlive; }

	void SetLifes(int amoutLives);
	void SetBackAlive();

	void notifySubject(bew::GameEvents event, bew::GameObject* object);
	
	virtual ~HealthComponent() = default;
	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) = delete;
private:
	int m_Lifes;
	bool m_IsAlive{true};
};



