#include <SDL.h>
#include "Texture2D.h"

bew::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

glm::ivec2 bew::Texture2D::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* bew::Texture2D::GetSDLTexture() const
{
	return m_pTexture;
}

bew::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_pTexture = texture;
}
