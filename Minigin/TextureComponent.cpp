#include "TextureComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(GameObject* pParentObject, const std::string& filename) : Component(pParentObject)
{
	SetTexture(filename);
}

void dae::TextureComponent::Render() const
{
	if (m_texture != nullptr)
	{
		const auto& pos = GetParentObject()->GetTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

std::shared_ptr<dae::Texture2D> dae::TextureComponent::GetTexture()
{
	return m_texture;
}
