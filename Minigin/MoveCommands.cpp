#include "MoveCommands.h"

#include "GameObject.h"
#include "PlayerMovement.h"

void dae::MoveUp::Execute(GameObject& gameobject)
{
	auto comp = gameobject.GetComponent<PlayerMovement>();
	if(comp)
	{
		comp->MoveUp();
	}
	return;
}

void dae::MoveDown::Execute(GameObject& gameobject)
{
	auto comp = gameobject.GetComponent<PlayerMovement>();
	if (comp)
	{
		comp->MoveDown();
	}
	return;
}

void dae::MoveLeft::Execute(GameObject& gameobject)
{
	auto comp = gameobject.GetComponent<PlayerMovement>();
	if (comp)
	{
		comp->MoveLeft();
	}
	return;
}

void dae::MoveRight::Execute(GameObject& gameobject)
{
	auto comp = gameobject.GetComponent<PlayerMovement>();
	if (comp)
	{
		comp->MoveRight();
	}
	return;
}
