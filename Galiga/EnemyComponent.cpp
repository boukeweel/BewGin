#include "EnemyComponent.h"

#include <iostream>

#include "GameObject.h"
#include "HitBoxComponent.h"
#include "ObjectPoolingComponent.h"
#include "PoolComponent.h"

EnemyComponent::EnemyComponent(bew::GameObject* pParentObject, bew::GameObject* Player): Component(pParentObject),m_pPlayer{ Player }
{
	if(m_pPlayer->HasComponent<ObjectPoolingComponent>())
	{
		m_pBulletVector = m_pPlayer->GetComponent<ObjectPoolingComponent>()->GetObjectList();
	}
}

void EnemyComponent::FixedUpdate()
{
	CheckInHitBox();
}

void EnemyComponent::CheckInHitBox()
{
	for (const auto& bullet : *m_pBulletVector)
	{
		if (bullet->GetComponent<PoolComponent>()->InUse())
		{
			if (GetParentObject()->GetComponent<bew::HitBoxComponent>()->InsideHitBox(bullet->GetComponent<bew::HitBoxComponent>()->GetHitBox()))
			{
				bullet->GetComponent<PoolComponent>()->SetInUse(false);
				bullet->SetIsActive(false);

				GetParentObject()->SetIsActive(false);
			}
		}
	}
}
