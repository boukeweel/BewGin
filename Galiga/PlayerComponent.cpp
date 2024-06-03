#include "PlayerComponent.h"

#include <iostream>

#include "BewGin.h"
#include "EnemyComponent.h"
#include "GameEntityData.h"
#include "HitBoxComponent.h"
#include "Texture2D.h"
#include "TextureComponent.h"

PlayerComponent::PlayerComponent(bew::GameObject* pparentObject) :Component(pparentObject)
{
	GetEnemies();
}

void PlayerComponent::FixedUpdate()
{
	CheckCollsion();
	constrainPlayerPosition();
}

void PlayerComponent::CheckCollsion()
{
	for (const auto& Enemy : *m_pEnemies)
	{
		if(Enemy->GetIsActive())
		{
			if(GetParentObject()->GetComponent<bew::HitBoxComponent>()->InsideHitBox(Enemy))
			{
				Enemy->GetComponent<EnemyComponent>()->TakeDamages(GetParentObject());
				
				std::cout << "Player hit\n";
				//todo add shit for reusing enemy

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
