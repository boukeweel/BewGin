#include "LeaderBoardObserver.h"

LeaderBoardObserver::LeaderBoardObserver(LeaderBoardComponent* pLeaderBoardComponent) : m_LeaderBoard{pLeaderBoardComponent}
{
	
}


void LeaderBoardObserver::Notify(bew::GameEvents event, bew::GameObject*)
{
	switch (event)
	{
	case bew::GameEvents::UpdateLeaderBoard:
		m_LeaderBoard->UpdateLeaderBoared();
		break;
	}
}
