#include "SpriteSheetComponent.h"

#include <iostream>

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

bew::SpriteSheetComponent::SpriteSheetComponent(GameObject* pParentObject, const std::string& filename, int Rows, int Columns)
: Component(pParentObject),m_Rows{Rows},m_Columns{Columns}
{
	SetSpriteSheet(filename);
    SetSprite(0, 0);
}

bew::SpriteSheetComponent::SpriteSheetComponent(GameObject* pParentObject, std::shared_ptr<Texture2D> texture, int Rows, int Columns)
: Component(pParentObject),m_pTexture{ std::move(texture) },m_Rows{Rows},m_Columns{ Columns }
{
    SetSprite(0, 0);
}

void bew::SpriteSheetComponent::Render() const
{
    if (m_pTexture != nullptr) {
        const auto& pos = GetParentObject()->GetWorldPosition();
        const auto& scale = GetParentObject()->GetTransform().GetScale();

        float textureWidth = static_cast<float>(m_pTexture->GetSize().x);
        float textureHeight = static_cast<float>(m_pTexture->GetSize().y);

        float spriteWidth = (textureWidth / static_cast<float>(m_Columns)) * scale.x;
        float spriteHeight = (textureHeight / static_cast<float>(m_Rows)) * scale.y;

        float spriteSheetX = m_CurrentSprite.y * (textureWidth / static_cast<float>(m_Columns));
        float spriteSheetY = m_CurrentSprite.x * (textureHeight / static_cast<float>(m_Rows));

        Renderer::GetInstance().RenderTexture(*m_pTexture,
            pos.x - spriteWidth / 2, pos.y - spriteHeight / 2,
            spriteWidth, spriteHeight,
            spriteSheetX, spriteSheetY,
            textureWidth / static_cast<float>(m_Columns), textureHeight / static_cast<float>(m_Rows),
            GetParentObject()->GetTransform().GetRotation().x);
    }

}

void bew::SpriteSheetComponent::SetSpriteSheet(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void bew::SpriteSheetComponent::SetSprite(int row, int column)
{
	m_CurrentSprite = { row,column };
}

