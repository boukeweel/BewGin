#include "Subject.h"
void bew::Subject::AddObserver(std::unique_ptr<Observer> observer)
{
	m_pObservers.emplace_back(std::move(observer));
}
void bew::Subject::RemoveObserver(Observer* observer)
{
	m_pObservers.erase(std::remove_if(std::begin(m_pObservers), std::end(m_pObservers),
		[observer](const std::unique_ptr<Observer>& ptr){ return ptr.get() == observer; }),
		std::end(m_pObservers));
}
void bew::Subject::notify(GameEvents event, GameObject* GameObject)
{
	for (const auto& observer : m_pObservers)
	{
		observer->Notify(event, GameObject);
	}
}
