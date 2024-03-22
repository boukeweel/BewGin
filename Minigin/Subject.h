#pragma once
#include <vector>

#include "memory"
#include "Observer.h"

namespace dae
{
	class Subject
	{
	public:
		//this could be a shared ptr because maybe multibole subjects need to have the same observer not sure tho
		void AddObserver(std::unique_ptr<Observer> observer);
		void RemoveObserver(Observer* observer);

		Subject() = default;
		~Subject() = default;

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;
	protected:
		void notify(GameEvents event, GameObject* GameObject);

	private:
		std::vector<std::unique_ptr<Observer>> m_Observers;
	};
}


