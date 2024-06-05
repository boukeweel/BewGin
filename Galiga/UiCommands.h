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

class InitialsMoving final :
	public bew::Command
{
public:
	InitialsMoving(bew::GameObject* TargetObject,glm::vec3 dir);
	void Execute() override;

	InitialsMoving(const InitialsMoving& other) = delete;
	InitialsMoving(InitialsMoving&& other) = delete;
	InitialsMoving& operator=(const InitialsMoving& other) = delete;
	InitialsMoving& operator=(InitialsMoving&& other) = delete;

private:
	bew::GameObject* m_pTargetObject;
	glm::vec3 m_Direction;
};

class InitialsSelecting final :
	public bew::Command
{
public:
	InitialsSelecting(bew::GameObject* TargetObject);
	void Execute() override;

	InitialsSelecting(const InitialsSelecting& other) = delete;
	InitialsSelecting(InitialsSelecting&& other) = delete;
	InitialsSelecting& operator=(const InitialsSelecting& other) = delete;
	InitialsSelecting& operator=(InitialsSelecting&& other) = delete;

private:
	bew::GameObject* m_pTargetObject;
};

class InitialFinish final :
	public bew::Command
{
public:
	InitialFinish(bew::GameObject* TargetObject);
	void Execute() override;

	InitialFinish(const InitialFinish& other) = delete;
	InitialFinish(InitialFinish&& other) = delete;
	InitialFinish& operator=(const InitialFinish& other) = delete;
	InitialFinish& operator=(InitialFinish&& other) = delete;

private:
	bew::GameObject* m_pTargetObject;
};



