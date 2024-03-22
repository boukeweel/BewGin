#pragma once
#include <vector>

#include "Component.h"
#include "memory"
#include "Observer.h"

namespace dae
{
	//not sure if this is correct
	class Subject : public Component
	{
	public:
		//this could be a shared ptr because maybe multibole subjects need to have the same observer not sure tho
		void AddObserver(std::unique_ptr<Observer> observer);
		void RemoveObserver(Observer* observer);
		std::vector<std::unique_ptr<Observer>> GetObservers() { return m_Observers; }

		Subject(GameObject* p);
		virtual ~Subject() = default;

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;
	protected:
		virtual void notify(const GameEvents& event, GameObject* GameObject);
	private:
		std::vector<std::unique_ptr<Observer>> m_Observers;
	};
}


