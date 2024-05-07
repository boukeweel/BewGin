#pragma once
#include <memory>
#include <string>

#include "Component.h"

namespace bew
{
	class Texture2D;

	class SpriteSheetComponent :
		public Component
	{
	public:
		SpriteSheetComponent(GameObject* pParentObject, const std::string& filename, int Rows,int Columns);
		SpriteSheetComponent(GameObject* pParentObject, std::shared_ptr<Texture2D>, int Rows, int Columns);

		void Render() const override;

		void SetSpriteSheet(const std::string& filename);
		void SetSprite(int row, int column);

		virtual ~SpriteSheetComponent() = default;
		SpriteSheetComponent(const SpriteSheetComponent& other) = delete;
		SpriteSheetComponent(SpriteSheetComponent&& other) = delete;
		SpriteSheetComponent& operator=(const SpriteSheetComponent& other) = delete;
		SpriteSheetComponent& operator=(SpriteSheetComponent&& other) = delete;
	private:

		std::shared_ptr<Texture2D> m_pTexture{};

		int m_Rows;
		int m_Columns;

		glm::ivec2 m_CurrentSprite;
	};
}


