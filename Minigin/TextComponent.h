#pragma once
#include <memory>

#include "Component.h"
#include "string"
#include "Transform.h"

namespace bew
{
	class Font;
	class Texture2D;

	class TextComponent final :
		public Component
	{
	public:
		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		void SetFont(std::shared_ptr<Font> font);
		void SetFontSize(unsigned int size);

		std::string getText() { return m_Text; }

		TextComponent(GameObject* pparentObject, const std::string& text, std::shared_ptr<Font> font);
		TextComponent(GameObject* pparentObject, std::shared_ptr<Font> font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTextTexture;
		int m_FontSize{};
	};

}

