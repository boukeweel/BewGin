#include "MoveCommands.h"

#include "GameObject.h"
#include "GameTime.h"
#include "PlayerComponent.h"

MoveCommand::MoveCommand(bew::GameObject* targetObject, const glm::vec3& Direction, float speed)
	:m_TargetObject{ targetObject }, m_Direction{ Direction }, m_Speed{ speed }
{
}

void MoveCommand::Execute()
{
	if(!m_TargetObject->GetIsActive() || !m_TargetObject->GetComponent<PlayerComponent>()->GetAllowedToMove())
		return;

	glm::vec3 velocity = glm::normalize(m_Direction) * m_Speed;

	m_TargetObject->Translate(velocity * bew::GameTime::GetDeltaTimeFloat());
}
