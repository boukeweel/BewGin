#pragma once
#include "Command.h"


namespace bew
{
	class GameObject;
}


class DammagesPlayer final : public bew::Command
{
public:
	DammagesPlayer(bew::GameObject* targetObject, int Dammages);
	void Execute() override;

	DammagesPlayer(const DammagesPlayer& other) = delete;
	DammagesPlayer(DammagesPlayer&& other) = delete;
	DammagesPlayer& operator=(const DammagesPlayer& other) = delete;
	DammagesPlayer& operator=(DammagesPlayer&& other) = delete;

private:
	bew::GameObject* m_TargetObject;
	int m_Damages;
};

class Score final : public bew::Command
{
public:
	Score(bew::GameObject* targetObject, int Dammages);
	void Execute() override;

	Score(const Score& other) = delete;
	Score(Score&& other) = delete;
	Score& operator=(const Score& other) = delete;
	Score& operator=(Score&& other) = delete;

private:
	bew::GameObject* m_TargetObject;
	int m_Score;
};




