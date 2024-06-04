#pragma once
#include "Command.h"
#include "GameObject.h"

class ArrowMove final :
    public bew::Command
{
public:
	ArrowMove(bew::GameObject* TargetObject, const glm::vec3& Direction);
	void Execute() override;

	ArrowMove(const ArrowMove& other) = delete;
	ArrowMove(ArrowMove&& other) = delete;
	ArrowMove& operator=(const ArrowMove& other) = delete;
	ArrowMove& operator=(ArrowMove&& other) = delete;

private:
	bew::GameObject* m_pTargetObject;
	glm::vec3 m_Direction;
};

class SelectOption final :
	public bew::Command
{
public:
	SelectOption(bew::GameObject* TargetObject);
	void Execute() override;

	SelectOption(const SelectOption& other) = delete;
	SelectOption(SelectOption&& other) = delete;
	SelectOption& operator=(const SelectOption& other) = delete;
	SelectOption& operator=(SelectOption&& other) = delete;

private:
	bew::GameObject* m_pTargetObject;
};

