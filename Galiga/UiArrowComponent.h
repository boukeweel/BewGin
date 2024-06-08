#pragma once
#include "Component.h"

class UiArrowComponent : public bew::Component
{
public:
	UiArrowComponent(bew::GameObject* pParentOjbect, int spaceBetween, int amountOptions);

	void MoveUp();
	void MoveDown();

	void Select();

	virtual ~UiArrowComponent() = default;
	UiArrowComponent(const UiArrowComponent& other) = delete;
	UiArrowComponent(UiArrowComponent&& other) = delete;
	UiArrowComponent& operator=(const UiArrowComponent& other) = delete;
	UiArrowComponent& operator=(UiArrowComponent&& other) = delete;
private:
	const int m_SpaceBetween;
	const int m_AmountOptions;
	int m_CurrentOption;
};

