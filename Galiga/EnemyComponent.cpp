#include "EnemyComponent.h"

#include <iostream>

#include "GameObject.h"
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
	std::cout << "fix\n";
}

void EnemyComponent::Update()
{
	std::cout << "upd\n";
	//todo
	//should be in fixxed update
	//and should be a collision component the 
	for (const auto& bullet : *m_pBulletVector)
	{
		if(bullet->GetComponent<PoolComponent>()->InUse())
		{

		}
	}
}
