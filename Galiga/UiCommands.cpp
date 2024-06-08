#include "UiCommands.h"

#include "InitialsComponent.h"
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
	m_pTargetObject->GetComponent<UiArrowComponent>()->Select();
}

//scoreboard Commands
InitialsMoving::InitialsMoving(bew::GameObject* TargetObject,glm::vec3 dir) : m_pTargetObject(TargetObject), m_Direction{dir}
{
}

void InitialsMoving::Execute()
{
	auto comp = m_pTargetObject->GetComponent<InitialsComponent>();
	if(comp)
	{
		if(static_cast<int>(m_Direction.x) == -1)
		{
			comp->MoveLeft();
		}
		else if(static_cast<int>(m_Direction.x) == 1)
		{
			comp->MoveRight();
		}
	}
}

InitialsSelecting::InitialsSelecting(bew::GameObject* TargetObject) : m_pTargetObject{TargetObject}
{
}

void InitialsSelecting::Execute()
{
	auto comp = m_pTargetObject->GetComponent<InitialsComponent>();
	if (comp)
	{
		comp->Select();
	}
}

InitialFinish::InitialFinish(bew::GameObject* TargetObject) : m_pTargetObject{ TargetObject }
{
}

void InitialFinish::Execute()
{
	auto comp = m_pTargetObject->GetComponent<InitialsComponent>();
	if (comp)
	{
		comp->Finish();
	}
}
