#pragma once


namespace bew
{
	class GameObject;
	//this should become something the user can add things to
	//todo add more events
	enum class GameEvents
	{
		PlayerDied,
		PlayerTookDamages,
		PlayerAddedScore,
		PlayerWon,
		TakeDamages,
		ObjectDied,
		UpdateLeaderBoard,
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



