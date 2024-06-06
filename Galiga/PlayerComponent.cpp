#include "PlayerComponent.h"

#include "BewGin.h"
#include "EnemyComponent.h"
#include "GameEntityData.h"
#include "GameTime.h"
#include "HealthComponent.h"
#include "HitBoxComponent.h"
#include "PoolComponent.h"
#include "SpriteSheetComponent.h"
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

void PlayerComponent::Update()
{
	SuckUpAnimation();
}

void PlayerComponent::StartSuckUpAnimation(bew::GameObject* beam)
{
	m_Beam = beam;
	m_BeingSuckedUp = true;
	m_AllowedToMove = false;
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

				PlayerGotHit();
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

void PlayerComponent::SuckUpAnimation()
{
	if(!m_BeingSuckedUp)
		return;

	glm::vec2 TargetPos;
	TargetPos.x = m_Beam->GetWorldPosition().x;
	TargetPos.y = m_Beam->GetWorldPosition().y - (static_cast<float>(m_Beam->GetComponent<bew::SpriteSheetComponent>()->GetTexture()->GetSize().y) - 50.f);

	const glm::vec2 dist = TargetPos - glm::vec2(GetParentObject()->GetWorldPosition().x, GetParentObject()->GetWorldPosition().y);
	const glm::vec2 velocity = glm::normalize(dist);

	GetParentObject()->Translate(glm::vec3(velocity, 0.0f) * bew::GameTime::GetDeltaTimeFloat() * 100.f);
	const float distance = glm::length(dist);

	if (distance < 3.f)
	{
		PlayerGotHit();
		m_BeingSuckedUp = false;
		m_Beam = nullptr;
	}

	float rotation = GetParentObject()->GetRotation() + 5;
	if (rotation >= 360)
		rotation = 0;
	GetParentObject()->SetRotation(rotation);
}

void PlayerComponent::PlayerGotHit()
{
	GetParentObject()->GetComponent<HealthComponent>()->TakeDammages(1);
	GetParentObject()->SetIsActive(false);
	GetParentObject()->GetComponent<bew::SubjectComponent>()->GetSubject()->notify(bew::GameEvents::PauseEnemyAttacking, GetParentObject());
	//todo add explotion + sound + other code what is needed
}

void PlayerComponent::GetEnemies()
{
	m_pEnemies = GameEntityData::GetInstance().GetEnemies();
}

