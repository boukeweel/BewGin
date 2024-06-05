#include "ShootCommand.h"

#include "BulletPool.h"
#include "SoundServiceLocator.h"

ShootCommand::ShootCommand(bew::GameObject* targetObject) : m_TargetObject{targetObject}
{
}

void ShootCommand::Execute()
{
	if (!m_TargetObject->GetIsActive())
		return;

	auto ObjPooling =m_TargetObject->GetComponent<BulletPool>();

	if(ObjPooling != nullptr)
	{
		ObjPooling->SetNextObjectActive();
	}
}
