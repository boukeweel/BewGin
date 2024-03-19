#include "MoveCommands.h"

#include "GameObject.h"
#include "GameTime.h"

dae::MoveCommand::MoveCommand(GameObject* targetObject, const glm::vec3& Direction, float speed)
	:m_TargetObject{ targetObject }, m_Direction{ Direction }, m_Speed{ speed }
{
}

void dae::MoveCommand::Execute()
{
	glm::vec3 velocity = glm::normalize(m_Direction) * m_Speed;

	m_TargetObject->Translate(velocity * GameTime::GetDeltaTimeFloat());
}
