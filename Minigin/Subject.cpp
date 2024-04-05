#include "Subject.h"
void bew::Subject::AddObserver(std::unique_ptr<Observer> observer)
{
	m_Observers.emplace_back(std::move(observer));
}
void bew::Subject::RemoveObserver(Observer* observer)
{
	m_Observers.erase(std::remove_if(std::begin(m_Observers), std::end(m_Observers),
		[observer](const std::unique_ptr<Observer>& ptr){ return ptr.get() == observer; }),
		std::end(m_Observers));
}
void bew::Subject::notify(GameEvents event, GameObject* GameObject)
{
	for (const auto& observer : m_Observers)
	{
		observer->Notify(event, GameObject);
	}
}
