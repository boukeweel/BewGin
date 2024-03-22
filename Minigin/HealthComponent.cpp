#include "HealthComponent.h"

#include "GameObject.h"

dae::HealthComponent::HealthComponent(GameObject* pparentObject, int lifes) : Component(pparentObject), m_Lifes{ lifes }
{
}

void dae::HealthComponent::TakeDammages(int amount)
{
	if(m_IsAlive)
	{
		m_Lifes -= amount;
		GetParentObject()->GetSubject()->notify(GameEvents::PlayerTookDamages, GetParentObject());
		
		if (m_Lifes == 0)
		{
			Died();
		}
		
	}
}

void dae::HealthComponent::Died()
{
	GetParentObject()->GetSubject()->notify(GameEvents::PlayerDied, GetParentObject());
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


