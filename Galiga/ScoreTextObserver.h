#pragma once
#include "Observer.h"
#include "TextComponent.h"


class ScoreTextObserver final :
	public bew::Observer
{
public:
	ScoreTextObserver(bew::TextComponent* pTextComponent);

	void Notify(bew::GameEvents event, bew::GameObject* gameObject) override;

	virtual ~ScoreTextObserver() = default;
	ScoreTextObserver(const ScoreTextObserver& other) = delete;
	ScoreTextObserver(ScoreTextObserver&& other) = delete;
	ScoreTextObserver& operator=(const ScoreTextObserver& other) = delete;
	ScoreTextObserver& operator=(ScoreTextObserver&& other) = delete;

private:
	bew::TextComponent* m_TextComponent;
	std::string m_ScoreTxt;
};



