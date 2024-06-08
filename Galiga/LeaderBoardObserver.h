#pragma once
#include "LeaderBoardComponent.h"
#include "Observer.h"
#include "SwitchSceneOnTimeComponent.h"

class LeaderBoardObserver :
	public bew::Observer
{
public:
	LeaderBoardObserver(LeaderBoardComponent* pLeaderBoardComponent,SwitchSceneOnTimeComponent* pSwitchSceneComponent);

	void Notify(bew::GameEvents event, bew::GameObject*) override;

	virtual ~LeaderBoardObserver() = default;
	LeaderBoardObserver(const LeaderBoardObserver& other) = delete;
	LeaderBoardObserver(LeaderBoardObserver&& other) = delete;
	LeaderBoardObserver& operator=(const LeaderBoardObserver& other) = delete;
	LeaderBoardObserver& operator=(LeaderBoardObserver&& other) = delete;
private:
	LeaderBoardComponent* m_pLeaderBoard;
	SwitchSceneOnTimeComponent* m_pSwitchScene;
};

