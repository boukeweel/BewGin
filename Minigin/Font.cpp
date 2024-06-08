#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* bew::Font::GetFont() const {
	return m_pFont;
}

bew::Font::Font(const std::string& fullPath, unsigned int size) : m_pFont(nullptr)
{
	m_pFont = TTF_OpenFont(fullPath.c_str(), size);
	if (m_pFont == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

bew::Font::~Font()
{
	TTF_CloseFont(m_pFont);
}

void bew::Font::ChangeSize(unsigned int /*newSize*/)
{
    //todo add the chance size function 
}
