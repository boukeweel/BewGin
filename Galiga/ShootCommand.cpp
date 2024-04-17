#include "ShootCommand.h"

#include "ObjectPoolingComponent.h"

ShootCommand::ShootCommand(bew::GameObject* targetObject) : m_TargetObject{targetObject}
{
}

void ShootCommand::Execute()
{
	if (!m_TargetObject->GetIsActive())
		return;

	auto ObjPooling =m_TargetObject->GetComponent<ObjectPoolingComponent>();

	if(ObjPooling != nullptr)
	{
		ObjPooling->SetNextObjectActive();
	}
}
