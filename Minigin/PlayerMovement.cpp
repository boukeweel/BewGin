#include "PlayerMovement.h"

#include "GameObject.h"

dae::PlayerMovement::PlayerMovement(GameObject* pParentObject, float speed)
: Component(pParentObject), m_speed{speed}, m_MoveDirection{0,0}
{
}

void dae::PlayerMovement::Update(float deltaTime)
{
	if(glm::length(m_MoveDirection) > 0)
	{
		glm::vec3 position = GetParentObject()->GetWorldPosition();

		position.x += m_MoveDirection.x * m_speed * deltaTime;
		position.y += m_MoveDirection.y * m_speed * deltaTime;

		GetParentObject()->SetPosition(position);
	}
}

//todo Not sure what is up 1 or -1 and left 1 or -1
void dae::PlayerMovement::MoveUp()
{
	m_MoveDirection.y = -1;
}

void dae::PlayerMovement::MoveDown()
{
	m_MoveDirection.y = 1;
}

void dae::PlayerMovement::MoveRight()
{
	m_MoveDirection.x = 1;
}

void dae::PlayerMovement::MoveLeft()
{
	m_MoveDirection.x = -1;
}

void dae::PlayerMovement::ReleaseUpDown()
{
	m_MoveDirection.y = 0;
}

void dae::PlayerMovement::ReleaseLeftRight()
{
	m_MoveDirection.x = 0;
}

void dae::PlayerMovement::SetSpeed(float speed)
{
	m_speed = speed;
}
