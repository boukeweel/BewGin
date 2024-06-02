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

        const float textureWidth = static_cast<float>(m_pTexture->GetSize().x);
        const float textureHeight = static_cast<float>(m_pTexture->GetSize().y);

        const float fullSpriteWidth = textureWidth / static_cast<float>(m_Columns);
        const float fullSpriteHeight = textureHeight / static_cast<float>(m_Rows);

        const float spriteWidth = fullSpriteWidth * m_SpriteSize.x * scale.x;
        const float spriteHeight = fullSpriteHeight * m_SpriteSize.y * scale.y;

        const float spriteSheetX = m_CurrentSprite.y * fullSpriteWidth + fullSpriteWidth * m_SpriteOffset.x;
        const float spriteSheetY = m_CurrentSprite.x * fullSpriteHeight + fullSpriteHeight * m_SpriteOffset.y;

        const float texturePartWidth = fullSpriteWidth * m_SpriteSize.x;
        const float texturePartHeight = fullSpriteHeight * m_SpriteSize.y;

        Renderer::GetInstance().RenderTexture(*m_pTexture,
            pos.x - (fullSpriteWidth * scale.x) / 2, pos.y - (fullSpriteHeight * scale.y )/ 2,
            spriteWidth, spriteHeight,
            spriteSheetX, spriteSheetY,
            texturePartWidth, texturePartHeight,
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

