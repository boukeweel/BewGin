#include "ShootCommand.h"

ShootCommand::ShootCommand(bew::GameObject* targetObject) : m_TargetObject{targetObject}
{
}

void ShootCommand::Execute()
{
	if (!m_TargetObject->GetIsActive())
		return;

	//spawn bullet 
}
