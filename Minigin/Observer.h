#pragma once


namespace dae
{
	class GameObject;
	//this should become something the user can add things to
	//todo add more events
	enum class GameEvents
	{
		PlayerDied,
		PlayerWon
	};

	class Observer
	{
	public:
		virtual void Notify(GameEvents event, GameObject* gameObject);


		Observer() = default;
		virtual ~Observer() = default;
		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;
	};
}



