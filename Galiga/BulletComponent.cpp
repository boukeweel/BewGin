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

	if (GetParentObject()->GetWorldPosition().y <= -10.f)
	{
		GetParentObject()->SetIsActive(false);
		if(poolComp != nullptr)
		{
			poolComp->SetInUse(false);
		}

	}
}
