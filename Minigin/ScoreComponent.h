#pragma once
#include "Component.h"

namespace bew
{
	enum class GameEvents;

	class ScoreComponent :
		public Component
	{
	public:
		void AddScore(int addAmount);
		int getScore() const { return m_Score; }

		ScoreComponent(GameObject* pparentObject);
		void notifySubject(GameEvents event, GameObject* object);
		virtual ~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

	private:
		void Won();

		bool m_Won{false};
		int m_Score{ 0 };
		int m_WinAmount{ 1000 };
	};
}




