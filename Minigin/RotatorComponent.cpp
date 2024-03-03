#include "RotatorComponent.h"

#include "GameObject.h"

dae::RotatorComponent::RotatorComponent(GameObject* pParentObject, float radius, float RotationSpeed):Component(pParentObject),m_Radius{ radius },m_RotationSpeed{RotationSpeed},m_CurrentRotation{0}
{
	m_Center = GetParentObject()->GetTransform().GetPosition();
}

void dae::RotatorComponent::Update(float deltaTime)
{
	m_CurrentRotation += m_RotationSpeed * deltaTime;

	if(GetParentObject())
	{
		const float x = m_Center.x + m_Radius * std::cos(m_CurrentRotation);
		const float y = m_Center.y + m_Radius * std::sin(m_CurrentRotation);

		GetParentObject()->SetPosition(x, y);
	}
}
