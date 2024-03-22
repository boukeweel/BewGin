#include "Subject.h"

//void dae::Subject::AddObserver(std::unique_ptr<Observer> observer)
//{
//	m_Observers.emplace_back(std::move(observer));
//}
//
//void dae::Subject::RemoveObserver(Observer* observer)
//{
//	/*m_Observers.erase(std::remove_if(std::begin(m_Observers), std::end(m_Observers),
//		[observer](const std::unique_ptr<Observer>& ptr){ return ptr.get() == observer; }),
//		std::end(m_Observers));*/
//}

dae::Subject::Subject(GameObject* pParentObject) : Component(pParentObject)
{
}


//void dae::Subject::notify(const GameEvents& event, GameObject* GameObject)
//{
//	for (const auto& observer : m_Observers)
//	{
//		observer->Notify(event, GameObject);
//	}
//}
