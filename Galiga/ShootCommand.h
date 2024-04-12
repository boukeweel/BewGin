#pragma once
#include <Command.h>

#include "GameObject.h"

class ShootCommand final : public bew::Command
{
public:
	ShootCommand(bew::GameObject* targetObject);
	void Execute() override;

	ShootCommand(const ShootCommand& other) = delete;
	ShootCommand(ShootCommand&& other) = delete;
	ShootCommand& operator=(const ShootCommand& other) = delete;
	ShootCommand& operator=(ShootCommand&& other) = delete;

private:
	bew::GameObject* m_TargetObject;

};

