#include "PlayerComponent.h"

#include <iostream>

#include "BewGin.h"
#include "EnemyComponent.h"
#include "GameEntityData.h"
#include "HealthComponent.h"
#include "HitBoxComponent.h"
#include "PoolComponent.h"
#include "SubjectComponent.h"
#include "Texture2D.h"
#include "TextureComponent.h"

PlayerComponent::PlayerComponent(bew::GameObject* pparentObject) :Component(pparentObject)
{
	GetEnemies();
}

void PlayerComponent::FixedUpdate()
{
	constrainPlayerPosition();
	CheckCollision();
}

void PlayerComponent::CheckCollision()
{
	for (const auto& Enemy : *m_pEnemies)
	{
		if(Enemy->GetIsActive() && Enemy->GetComponent<PoolComponent>()->InUse())
		{
			if(GetParentObject()->GetComponent<bew::HitBoxComponent>()->InsideHitBox(Enemy))
			{
				Enemy->GetComponent<EnemyComponent>()->TakeDamages(GetParentObject());

				GetParentObject()->GetComponent<HealthComponent>()->TakeDammages(1);

				//todo add explotion + sound + other code what is needed
			}
		}
	}
}

void PlayerComponent::constrainPlayerPosition()
{
	const glm::vec3 position = GetParentObject()->GetWorldPosition();
	const glm::ivec2 textureSize = GetParentObject()->GetComponent<bew::TextureComponent>()->GetTexture()->GetSize();
	int maxX = bew::ScreenWidth - 150; //magic number bad
	if(position.x <= static_cast<float>(textureSize.x))
	{
		GetParentObject()->SetPosition(static_cast<float>(textureSize.x), position.y);
	}

	if (position.x >= static_cast<float>(maxX))
	{
		GetParentObject()->SetPosition(static_cast<float>(maxX), position.y);
	}
}

void PlayerComponent::GetEnemies()
{
	m_pEnemies = GameEntityData::GetInstance().GetEnemies();
}
