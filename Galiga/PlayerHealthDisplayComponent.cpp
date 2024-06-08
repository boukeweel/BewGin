#include "PlayerHealthDisplayComponent.h"

#include "ObjectPreset.h"
#include "Scene.h"
#include "SceneManager.h"

PlayerHealthDisplayComponent::PlayerHealthDisplayComponent(bew::GameObject* pparentObject,int health,bool p2):Component(pparentObject),m_Health{ health - 1 }
{
	glm::vec3 objectPos = GetParentObject()->GetWorldPosition();
	if(p2 == false)
	{
		PlayerHealthIconP1 iconPreset;
		for (int i = 0; i < m_Health; ++i)
		{
			auto icon = iconPreset.Create();
			icon->SetPosition(objectPos.x + static_cast<float>(32 * i), objectPos.y);
			m_pDisplayObjects.emplace_back(icon.get());
			bew::SceneManager::GetInstance().AddToCurrentScene(std::move(icon));
		}
	}
	else
	{
		PlayerHealthIconP2 iconPreset;
		for (int i = 0; i < m_Health; ++i)
		{
			auto icon = iconPreset.Create();
			icon->SetPosition(objectPos.x + static_cast<float>(32 * i), objectPos.y);
			m_pDisplayObjects.emplace_back(icon.get());
			bew::SceneManager::GetInstance().AddToCurrentScene(std::move(icon));
		}
	}
	
}

void PlayerHealthDisplayComponent::RemoveHealthCount()
{
	if(m_Health == 0)
		return;
	for (size_t i = m_pDisplayObjects.size() - 1; i >= 0; --i)
	{
		if (m_pDisplayObjects[i]->GetIsActive())
		{
			m_pDisplayObjects[i]->SetIsActive(false);
			--m_Health; 
			break;
		}
	}
}

void PlayerHealthDisplayComponent::AddHealthCount()
{
	for (size_t i = 0; i < m_pDisplayObjects.size(); ++i)
	{
		if (!m_pDisplayObjects[i]->GetIsActive()) 
		{
			m_pDisplayObjects[i]->SetIsActive(true); 
			++m_Health; 
			break;
		}
	}
}

