#include "TextComponent.h"

#include <SDL_ttf.h>
#include <stdexcept>

#include "Font.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"

bew::TextComponent::TextComponent(GameObject* pparentObject,const std::string& text, std::shared_ptr<Font> font):
	m_NeedsUpdate(true), m_Text(text), m_pFont(std::move(font)), m_pTextTexture(nullptr), Component(pparentObject), m_FontSize{1}
{
}

bew::TextComponent::TextComponent(GameObject* pparentObject, std::shared_ptr<Font> font) : TextComponent(pparentObject," ",font)
{
}

void bew::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void bew::TextComponent::Render() const
{
	if (m_pTextTexture != nullptr)
	{
		const auto& pos = GetParentObject()->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_pTextTexture, pos.x, pos.y);
	}
}

void bew::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void bew::TextComponent::SetPosition(float x, float y)
{
	GetParentObject()->GetTransform().SetPosition(x, y, 0.0f);
}

void bew::TextComponent::SetFont(std::shared_ptr<Font> font)
{
	m_pFont = std::move(font);
	m_NeedsUpdate = true;
}

void bew::TextComponent::SetFontSize(unsigned int size)
{
	m_pFont->ChangeSize(size);
}


