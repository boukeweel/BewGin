#include "StarComponent.h"

#include "BewGin.h"
#include "GameObject.h"
#include "GameTime.h"
#include "RandomFunctions.h"
#include "SpriteSheetComponent.h"

StarComponent::StarComponent(bew::GameObject* pParentObject) : Component(pParentObject)
{
	ResetStar();

	int randomWidth = bew::RandomFunctions::RandomI(bew::ScreenWidth);
	int randomHeight = bew::RandomFunctions::RandomI(bew::ScreenHeight);
	GetParentObject()->SetPosition(static_cast<float>(randomWidth), static_cast<float>(randomHeight));
}

void StarComponent::Update()
{
	if(GetParentObject()->GetWorldPosition().y > bew::ScreenHeight + 10)
	{
		ResetStar();
	}

	glm::vec3 velocity = glm::vec3(0.0f, 1.0f, 0.0f) * m_speed;

	GetParentObject()->Translate(velocity * bew::GameTime::GetDeltaTimeFloat());
}

void StarComponent::ResetStar()
{
	ResetPostion();
	ResetScale();
	RandomStar();
	RandomSpeed();
}

void StarComponent::ResetPostion()
{
	int randomWidth = bew::RandomFunctions::RandomI(bew::ScreenWidth);
	GetParentObject()->SetPosition(static_cast<float>(randomWidth), -10);
}

void StarComponent::RandomStar()
{
	
	int randomIndex = bew::RandomFunctions::RandomI(4);
	GetParentObject()->GetComponent<bew::SpriteSheetComponent>()->SetSprite(0, randomIndex);
}

void StarComponent::ResetScale()
{
	float randomScale = bew::RandomFunctions::RandomF(0.5f, 1.f);
	GetParentObject()->SetScale(randomScale, randomScale);
}

void StarComponent::RandomSpeed()
{
	m_speed = bew::RandomFunctions::RandomF(50, 100);
}

