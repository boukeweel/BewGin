#include "LeaderBoardObserver.h"

#include "GameData.h"

LeaderBoardObserver::LeaderBoardObserver(LeaderBoardComponent* pLeaderBoardComponent, SwitchSceneOnTimeComponent* pSwitchSceneComponent) : m_pLeaderBoard{pLeaderBoardComponent}, m_pSwitchScene{pSwitchSceneComponent}
{
	
}


void LeaderBoardObserver::Notify(bew::GameEvents event, bew::GameObject*)
{
	if(event == bew::GameEvents::UpdateLeaderBoard)
	{
		m_pLeaderBoard->UpdateLeaderBoard();
		m_pSwitchScene->StartTwoPlayers();
	}
}
