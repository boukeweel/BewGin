#pragma once


namespace bew
{
	class GameObject;
	enum class GameEvents
	{
		PlayerDied,
		PlayerTookDamages,
		PlayerAddedScore,
		TakeDamages,
		ObjectDied,
		UpdateLeaderBoard,
		PauseEnemyAttacking,
		UnPauseEnemyAttacking,
		Died,
	};

	class Observer
	{
	public:
		virtual void Notify(GameEvents event, GameObject* gameObject) = 0;

		Observer() = default;
		virtual ~Observer() = default;
		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;
	};
}



