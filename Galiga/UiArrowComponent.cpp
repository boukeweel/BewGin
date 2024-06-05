#include "UiArrowComponent.h"

#include <iostream>

#include "GameData.h"
#include "GameObject.h"
#include "Scene.h"

UiArrowComponent::UiArrowComponent(bew::GameObject* pParentOjbect, int spaceBetween, int amountOptions)
: Component(pParentOjbect), m_SpaceBetween{spaceBetween}, m_AmountOptions{ amountOptions },m_CurrentOption{1}
{
}

void UiArrowComponent::MoveUp()
{
	if (m_CurrentOption != 1)
	{
		m_CurrentOption--;
		glm::vec3 pos = GetParentObject()->GetWorldPosition();
		GetParentObject()->SetPosition(pos.x, pos.y - static_cast<float>(m_SpaceBetween));
	}
}

void UiArrowComponent::MoveDown()
{
	if(m_CurrentOption != m_AmountOptions)
	{
		m_CurrentOption++;
		glm::vec3 pos = GetParentObject()->GetWorldPosition();
		GetParentObject()->SetPosition(pos.x, pos.y + static_cast<float>(m_SpaceBetween));
	}
}

void UiArrowComponent::Selcet()
{
	if (m_CurrentOption == 1)
		GameData::GetInstance().SetTwoPlayers(false);
	else if(m_CurrentOption == 2)
		GameData::GetInstance().SetTwoPlayers(true);

	GameData::GetInstance().ResetShots();
	bew::SceneManager::GetInstance().SwitchScene(1);
}