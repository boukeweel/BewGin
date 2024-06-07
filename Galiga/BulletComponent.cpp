#include "BulletComponent.h"

#include "GameObject.h"
#include "GameTime.h"

BulletComponent::BulletComponent(bew::GameObject* pParentObject, float speed):Component(pParentObject),m_Speed{speed}
{
	poolComp = GetParentObject()->GetComponent<PoolComponent>();
}

void BulletComponent::Update()
{
	GetParentObject()->Translate(m_Direction * m_Speed * bew::GameTime::GetDeltaTimeFloat());

	bool reset{false};
	if(m_Direction.y == -1.f && GetParentObject()->GetWorldPosition().y <= m_ResetHeight)
	{
		reset = true;
	}
	else if(m_Direction.y == 1.f && GetParentObject()->GetWorldPosition().y >= m_ResetHeight)
	{
		reset = true;
	}

	if(reset)
	{
		GetParentObject()->SetIsActive(false);
		if (poolComp != nullptr)
		{
			poolComp->SetInUse(false);
		}
	}
}
