#include "UiCommands.h"

#include "UiArrowComponent.h"

ArrowMove::ArrowMove(bew::GameObject* TargetObject, const glm::vec3& Direction) :m_pTargetObject{TargetObject},m_Direction(Direction)
{
}

void ArrowMove::Execute()
{
	auto comp = m_pTargetObject->GetComponent<UiArrowComponent>();

	if(static_cast<int>(m_Direction.y) == 1)
	{
		comp->MoveUp();
	}
	else if(static_cast<int>(m_Direction.y) == -1)
	{
		comp->MoveDown();
	}
}

SelectOption::SelectOption(bew::GameObject* TargetObject) : m_pTargetObject{TargetObject}
{
}

void SelectOption::Execute()
{
	m_pTargetObject->GetComponent<UiArrowComponent>()->Selcet();
}
