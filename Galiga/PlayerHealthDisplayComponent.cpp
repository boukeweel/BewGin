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
		//magic number bad
		for (int i = 0; i < m_Health; ++i)
		{
			auto icon = iconPreset.Create();
			icon->SetPosition(objectPos.x + static_cast<float>(32 * i), objectPos.y);
			m_DisplayObjects.emplace_back(icon.get());
			bew::SceneManager::GetInstance().AddToCurrentScene(std::move(icon));
		}
	}
	else
	{
		PlayerHealthIconP2 iconPreset;
		//magic number bad
		for (int i = 0; i < m_Health; ++i)
		{
			auto icon = iconPreset.Create();
			icon->SetPosition(objectPos.x + static_cast<float>(32 * i), objectPos.y);
			m_DisplayObjects.emplace_back(icon.get());
			bew::SceneManager::GetInstance().AddToCurrentScene(std::move(icon));
		}
	}
	
}

void PlayerHealthDisplayComponent::RemoveHealthCount()
{
	if(m_Health == 0)
		return;
	for (size_t i = m_DisplayObjects.size() - 1; i >= 0; --i)
	{
		if (m_DisplayObjects[i]->GetIsActive())
		{
			m_DisplayObjects[i]->SetIsActive(false);
			--m_Health; 
			break;
		}
	}
}

void PlayerHealthDisplayComponent::AddHealthCount()
{
	for (size_t i = 0; i < m_DisplayObjects.size(); ++i)
	{
		if (!m_DisplayObjects[i]->GetIsActive()) 
		{
			m_DisplayObjects[i]->SetIsActive(true); 
			++m_Health; 
			break;
		}
	}
}

