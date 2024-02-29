#include "TextComponent.h"

#include <SDL_ttf.h>
#include <stdexcept>

#include "Font.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(GameObject* pparentObject,const std::string& text, std::shared_ptr<Font> font):
	m_NeedsUpdate(true), m_Text(text), m_pFont(std::move(font)), m_pTextTexture(nullptr), Component(pparentObject)
{
}

void dae::TextComponent::Update(float deltaTime)
{
	deltaTime += 1;

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

void dae::TextComponent::Render() const
{
	if (m_pTextTexture != nullptr)
	{
		const auto& pos = GetParentObject()->GetTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTextTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetPosition(float x, float y)
{
	GetParentObject()->GetTransform().SetPosition(x, y, 0.0f);
}

void dae::TextComponent::SetFont(std::shared_ptr<Font> font)
{
	m_pFont = std::move(font);
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetFontSize(int size)
{
	m_FontSize = size;
}


