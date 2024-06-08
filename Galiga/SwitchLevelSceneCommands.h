#pragma once
#include "Command.h"

namespace bew
{
	class GameObject;
}

class NextWave final : public bew::Command
{
public:
	NextWave(bew::GameObject* pTargetObject);
	void Execute() override;

	NextWave(const NextWave& other) = delete;
	NextWave(NextWave&& other) = delete;
	NextWave& operator=(const NextWave& other) = delete;
	NextWave& operator=(NextWave&& other) = delete;

	bew::GameObject* m_pTargetObject;
};

class NextScene final : public bew::Command
{
public:
	NextScene(bew::GameObject* pTargetObject);
	void Execute() override;

	NextScene(const NextScene& other) = delete;
	NextScene(NextScene&& other) = delete;
	NextScene& operator=(const NextScene& other) = delete;
	NextScene& operator=(NextScene&& other) = delete;

	bew::GameObject* m_pTargetObject;
};

