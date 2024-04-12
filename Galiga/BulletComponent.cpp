#include "BulletComponent.h"

#include "GameObject.h"
#include "GameTime.h"

BulletComponent::BulletComponent(bew::GameObject* pParentObject, float speed):Component(pParentObject),m_Speed{speed}
{
}

void BulletComponent::Update()
{
	GetParentObject()->Translate(m_Direction * m_Speed * bew::GameTime::GetDeltaTimeFloat());
}
