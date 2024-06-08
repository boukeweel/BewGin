#pragma once
#include <memory>
#include <string>

#include "Component.h"

namespace bew
{
	class Texture2D;

	class SpriteSheetComponent final:
		public Component
	{
	public:
		SpriteSheetComponent(GameObject* pParentObject, const std::string& filename, int Rows,int Columns);
		SpriteSheetComponent(GameObject* pParentObject, std::shared_ptr<Texture2D>, int Rows, int Columns);

		void Render() const override;

		void SetSprite(int row, int column);

		void SetSpriteOffset(const glm::vec2& offset) { m_SpriteOffset = offset; }
		void SetSpriteSize(const glm::vec2& size) { m_SpriteSize = size; }

		const Texture2D* GetTexture() const { return m_pTexture.get(); }

		virtual ~SpriteSheetComponent() = default;
		SpriteSheetComponent(const SpriteSheetComponent& other) = delete;
		SpriteSheetComponent(SpriteSheetComponent&& other) = delete;
		SpriteSheetComponent& operator=(const SpriteSheetComponent& other) = delete;
		SpriteSheetComponent& operator=(SpriteSheetComponent&& other) = delete;
	private:
		void SetSpriteSheet(const std::string& filename);
		std::shared_ptr<Texture2D> m_pTexture{};

		glm::vec2 m_SpriteOffset = glm::vec2(0.0f, 0.0f);
		glm::vec2 m_SpriteSize = glm::vec2(1.0f, 1.0f);

		glm::ivec2 m_TextureSize;

		int m_Rows;
		int m_Columns;

		glm::ivec2 m_CurrentSprite;
	};
}


