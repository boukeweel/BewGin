#pragma once
#include "Observer.h"
#include "TextComponent.h"


class LivesTextObserver final :
	public bew::Observer
{
public:
	LivesTextObserver(bew::TextComponent* pTextComponent);

	void Notify(bew::GameEvents event, bew::GameObject* gameObject) override;

	virtual ~LivesTextObserver() = default;
	LivesTextObserver(const LivesTextObserver& other) = delete;
	LivesTextObserver(LivesTextObserver&& other) = delete;
	LivesTextObserver& operator=(const LivesTextObserver& other) = delete;
	LivesTextObserver& operator=(LivesTextObserver&& other) = delete;

private:
	bew::TextComponent* m_TextComponent;
	std::string m_livesTxt;
};

