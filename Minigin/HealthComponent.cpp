#include "HealthComponent.h"

dae::HealthComponent::HealthComponent(GameObject* pparentObject, int lifes) : Component(pparentObject), m_Lifes{ lifes }
{
}

void dae::HealthComponent::TakeDammages(int amount)
{
	if(m_IsAlive)
	{
		m_Lifes -= amount;
		if (m_Lifes == 0)
		{
			Died();
		}

		//todo update teks idk what I should do with observer or just pass it true
	}
}

void dae::HealthComponent::Died()
{
	//todo notify a observer
	m_IsAlive = false;
}

void dae::HealthComponent::SetLifes(int amoutLives)
{
	if (!m_IsAlive)
		m_IsAlive = true;

	m_Lifes = amoutLives;
}

void dae::HealthComponent::SetBackAlive()
{
	SetLifes(1);
}


