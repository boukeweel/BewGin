#pragma once
#include "Observer.h"
#include "PlayerHealthDisplayComponent.h"


class LivesDisplayObserver final :
	public bew::Observer
{
public:
	LivesDisplayObserver(PlayerHealthDisplayComponent* pHealthDisplay);

	void Notify(bew::GameEvents event, bew::GameObject*) override;

	virtual ~LivesDisplayObserver() = default;
	LivesDisplayObserver(const LivesDisplayObserver& other) = delete;
	LivesDisplayObserver(LivesDisplayObserver&& other) = delete;
	LivesDisplayObserver& operator=(const LivesDisplayObserver& other) = delete;
	LivesDisplayObserver& operator=(LivesDisplayObserver&& other) = delete;

private:
	PlayerHealthDisplayComponent* m_pDisplayHealth;
};

