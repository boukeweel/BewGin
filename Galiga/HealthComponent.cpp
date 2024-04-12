#include "HealthComponent.h"

#include "GameObject.h"
#include "SubjectComponent.h"

HealthComponent::HealthComponent(bew::GameObject* pparentObject, int lifes) : Component(pparentObject), m_Lifes{ lifes }
{
}

void HealthComponent::notifySubject(bew::GameEvents event, bew::GameObject* object)
{
	object->GetComponent<bew::SubjectComponent>()->GetSubject()->notify(event, object);
}

void HealthComponent::TakeDammages(int amount)
{
	if(m_IsAlive)
	{
		m_Lifes -= amount;

		notifySubject(bew::GameEvents::PlayerTookDamages, GetParentObject());
		
		if (m_Lifes == 0)
		{
			Died();
		}
	}
}

void HealthComponent::Died()
{
	notifySubject(bew::GameEvents::PlayerDied, GetParentObject());
	m_IsAlive = false;
}

void HealthComponent::SetLifes(int amoutLives)
{
	if (!m_IsAlive)
		m_IsAlive = true;

	m_Lifes = amoutLives;
}

void HealthComponent::SetBackAlive()
{
	SetLifes(1);
}

