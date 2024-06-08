#include "LeaderBoardObserver.h"

LeaderBoardObserver::LeaderBoardObserver(LeaderBoardComponent* pLeaderBoardComponent) : m_pLeaderBoard{pLeaderBoardComponent}
{
	
}


void LeaderBoardObserver::Notify(bew::GameEvents event, bew::GameObject*)
{
	if(event == bew::GameEvents::UpdateLeaderBoard)
		m_pLeaderBoard->UpdateLeaderBoard();
}
