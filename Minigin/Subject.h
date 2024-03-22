#pragma once
#include <vector>
#include "memory"
#include "Observer.h"

namespace dae
{
	class Subject
	{
	public:
		void AddObserver(std::unique_ptr<Observer> observer);
		void RemoveObserver(Observer* observer);

		void notify(GameEvents event, GameObject* GameObject);

		Subject() = default;
		~Subject() = default;

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;
	private:
		std::vector<std::unique_ptr<Observer>> m_Observers;
	};
}


