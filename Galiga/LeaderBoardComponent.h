#pragma once
#include <Component.h>
#include <vector>

class LeaderBoardComponent :
    public bew::Component
{
public:
	LeaderBoardComponent(bew::GameObject* pParentOjbect);

	void UpdateLeaderBoared();

	virtual ~LeaderBoardComponent() = default;
	LeaderBoardComponent(const LeaderBoardComponent& other) = delete;
	LeaderBoardComponent(LeaderBoardComponent&& other) = delete;
	LeaderBoardComponent& operator=(const LeaderBoardComponent& other) = delete;
	LeaderBoardComponent& operator=(LeaderBoardComponent&& other) = delete;
private:
	std::vector<bew::GameObject*> m_Enteries;
};

