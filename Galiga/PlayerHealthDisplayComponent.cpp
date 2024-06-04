#include "PlayerHealthDisplayComponent.h"

#include "ObjectPreset.h"
#include "Scene.h"
#include "SceneManager.h"

PlayerHealthDisplayComponent::PlayerHealthDisplayComponent(bew::GameObject* pparentObject,int health):Component(pparentObject),m_Health{ health }
{
	PlayerHealthIcon iconPreset;
	glm::vec3 objectPos = GetParentObject()->GetWorldPosition();
	//magic number bad
	for (int i = 0; i < health; ++i)
	{
		auto icon = iconPreset.Create();
		icon->SetPosition(objectPos.x + static_cast<float>(32 * i), objectPos.y);
		m_DisplayObjects.emplace_back(icon.get());
		bew::SceneManager::GetInstance().GetCurrentScene().Add(std::move(icon));
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

