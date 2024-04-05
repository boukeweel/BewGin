#include "HealthComponent.h"

#include "GameObject.h"
#include "SubjectComponent.h"

bew::HealthComponent::HealthComponent(GameObject* pparentObject, int lifes) : Component(pparentObject), m_Lifes{ lifes }
{
}

void bew::HealthComponent::notifySubject(GameEvents event, GameObject* object)
{
	object->GetComponent<SubjectComponent>()->GetSubject()->notify(event, object);
}

void bew::HealthComponent::TakeDammages(int amount)
{
	if(m_IsAlive)
	{
		m_Lifes -= amount;

		notifySubject(GameEvents::PlayerTookDamages, GetParentObject());
		
		if (m_Lifes == 0)
		{
			Died();
		}
	}
}

void bew::HealthComponent::Died()
{
	notifySubject(GameEvents::PlayerDied, GetParentObject());
	m_IsAlive = false;
}

void bew::HealthComponent::SetLifes(int amoutLives)
{
	if (!m_IsAlive)
		m_IsAlive = true;

	m_Lifes = amoutLives;
}

void bew::HealthComponent::SetBackAlive()
{
	SetLifes(1);
}


