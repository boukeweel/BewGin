#include "EnemyComponent.h"

#include <iostream>

#include "GameObject.h"
#include "HitBoxComponent.h"
#include "ObjectPoolingComponent.h"
#include "PoolComponent.h"
#include "ScoreComponent.h"
#include "SubjectComponent.h"

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
		auto bulletPoolComp = bullet->GetComponent<PoolComponent>();

		if (bulletPoolComp->InUse())
		{
			if (GetParentObject()->GetComponent<bew::HitBoxComponent>()->InsideHitBox(bullet))
			{
				bulletPoolComp->SetInUse(false);
				bullet->SetIsActive(false);

				GetParentObject()->SetIsActive(false);

				//todo kinda wack ngl
				m_pPlayer->GetComponent<ScoreComponent>()->AddScore(100);
			}
		}
	}
}
