#include "SpriteSheetComponent.h"

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
        float spriteWidth = static_cast<float>(m_pTexture->GetSize().x) / static_cast<float>(m_Columns) * scale.x;
        float spriteHeight = static_cast<float>(m_pTexture->GetSize().y) / static_cast<float>(m_Rows) * scale.y;

        float spriteSheetX = m_CurrentSprite.y * (spriteWidth / scale.x);
        float spriteSheetY = m_CurrentSprite.x * (spriteHeight / scale.y);

        Renderer::GetInstance().RenderTexture(*m_pTexture,
            pos.x - spriteWidth / 2, pos.y - spriteHeight / 2,
            spriteWidth, spriteHeight,
            spriteSheetX, spriteSheetY,
            spriteWidth, spriteHeight,
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

