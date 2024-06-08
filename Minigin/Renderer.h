#pragma once
#include <SDL.h>

#include "Singleton.h"

namespace bew
{
	class Texture2D;
	
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_pRenderer{};
		SDL_Window* m_pWindow{};
		SDL_Color m_pClearColor{};

	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y, const float angle = 0) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, const float angle = 0) const;
		void RenderTexture(const Texture2D& texture, const float x, const float y, const float spriteWidth, const float spriteHeight, const float srcX, const float srcY, const float srcWidth, const float srcHeight, const float angle) const;

		void RenderRect(const SDL_Rect& rect) const;

		void DrawLine(float sX, float sY, float eX, float eY) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_pClearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_pClearColor = color; }
	};
}

