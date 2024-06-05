#pragma once
#include "Singleton.h"
#include <cmath>

class GameData : public bew::Singleton<GameData>
{
public:
	bool GetTwoPlayers() const { return m_TwoPlayers; }
	void SetTwoPlayers(bool value) { m_TwoPlayers = value; }

	int GetCurrentScoreP1() const { return m_CurrentScoreP1; }
	void SetCurrentScoreP1(int score) { m_CurrentScoreP1 = score; }

	int GetCurrentScoreP2() const { return m_CurrentScoreP2; }
	void SetCurrentScoreP2(int score) { m_CurrentScoreP2 = score; }

	int GetShotsFired() const { return m_ShotsFired; }
	int GetShotsHit() const { return m_ShotsHit; }
	void FireShot() { m_ShotsFired++; }
	void ShotHit() { m_ShotsHit++; }

	float GetHitMisRatio() const
	{
		if (m_ShotsFired == 0) {
			return 0.0f; // To avoid division by zero
		}
		float ratio = (static_cast<float>(m_ShotsHit) / m_ShotsFired) * 100.0f;
		return static_cast<float>(static_cast<int>(ratio * 10.f)) / 10.f;
	}

	void ResetShots()
	{
		m_ShotsFired = 0;
		m_ShotsHit = 0;
	}


private:
	friend class Singleton<GameData>;
	GameData() = default;

	bool m_TwoPlayers{ false };
	int m_CurrentScoreP1{ 0 };
	int m_CurrentScoreP2{ 0 };

	//shot data
	int m_ShotsFired{ 0 };
	int m_ShotsHit{ 0 };

	

};

