#include "RotatorComponent.h"

#include "GameObject.h"
#include <SDL_stdinc.h>

#include "GameTime.h"

bew::RotatorComponent::RotatorComponent(GameObject* pParentObject, float radius, float RotationSpeed):Component(pParentObject),m_Radius{ radius },m_RotationSpeed{RotationSpeed},m_CurrentRotation{0}
{
	m_Center = GetParentObject()->GetTransform().GetPosition();
}

void bew::RotatorComponent::Update()
{
	m_CurrentRotation += m_RotationSpeed * GameTime::GetDeltaTimeFloat();

	float TwoPi = 2 * static_cast<float>(M_PI);

	if (m_CurrentRotation > TwoPi)
		m_CurrentRotation -= TwoPi;

	if(GetParentObject())
	{
		const float x = m_Center.x + m_Radius * std::cos(m_CurrentRotation);
		const float y = m_Center.y + m_Radius * std::sin(m_CurrentRotation);

		GetParentObject()->SetPosition(x, y);
	}
}
