#include "LivesDisplayObserver.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

LivesDisplayObserver::LivesDisplayObserver(PlayerHealthDisplayComponent* pDisplayComponent) : m_DisplayHealth{ pDisplayComponent }
{
}

void LivesDisplayObserver::Notify(bew::GameEvents event, bew::GameObject* )
{
	switch (event)
	{
	case bew::GameEvents::TakeDamages:
		m_DisplayHealth->RemoveHealthCount();
		break;
	case bew::GameEvents::ObjectDied:
		//todo end game
		break;
	}

}
