#pragma once
#include "Singleton.h"

class GameData : public bew::Singleton<GameData>
{
public:
	bool GetTwoPlayers() const { return m_TwoPlayers; }
	void SetTwoPlayers(bool value) { m_TwoPlayers = value; }

	int GetCurrentScoreP1() const { return m_CurrentScoreP1; }
	void SetCurrentScoreP1(int score) { m_CurrentScoreP1 = score; }

	int GetCurrentScoreP2() const { return m_CurrentScoreP2; }
	void SetCurrentScoreP2(int score) { m_CurrentScoreP2 = score; }

private:
	friend class Singleton<GameData>;
	GameData() = default;

	bool m_TwoPlayers{false};
	int m_CurrentScoreP1{0};
	int m_CurrentScoreP2{0};
};

