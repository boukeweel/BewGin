#include "TextureComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

dae::TextureComponent::TextureComponent(GameObject* pParentObject, const std::string& filename) : Component(pParentObject)
{
	SetTexture(filename);
}

void dae::TextureComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const auto& pos = GetParentObject()->GetWorldPosition();
		float width  = static_cast<float>(m_pTexture->GetSize().x);
		float height = static_cast<float>(m_pTexture->GetSize().y);

		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x - width / 2, pos.y - height / 2 , width,height);
	}
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

std::shared_ptr<dae::Texture2D> dae::TextureComponent::GetTexture()
{
	return m_pTexture;
}
