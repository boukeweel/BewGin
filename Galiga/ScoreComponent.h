#pragma once
#include "Component.h"


namespace bew
{
	enum class GameEvents;
}

class ScoreComponent final :
	public bew::Component
{
public:
	void AddScore(int addAmount);
	int getScore() const { return m_Score; }

	ScoreComponent(bew::GameObject* pparentObject);
	void notifySubject(bew::GameEvents event, bew::GameObject* object);

	virtual ~ScoreComponent() = default;
	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) = delete;
private:
	bool m_Won{false};
	int m_Score{ 0 };
};





