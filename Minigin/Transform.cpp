#include "Transform.h"

void bew::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void bew::Transform::SetPosition(glm::vec3& pos)
{
	SetPosition(pos.x, pos.y, pos.z);
}

void bew::Transform::SetRotation(float x, float y, float z)
{
	m_Rotation.x = x;
	m_Rotation.y = y;
	m_Rotation.z = z;
}

void bew::Transform::SetScale(float x, float y, float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}
