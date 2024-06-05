#pragma once
#include <Component.h>
#include <memory>
#include <SDL_pixels.h>
#include <string>

#include "Font.h"

class HighScoreEntryComponent :
    public bew::Component
{
public:
	HighScoreEntryComponent(bew::GameObject* pParentOjbect);

	void CreateTextObjects(int number, int score, const std::string& initials);

	virtual ~HighScoreEntryComponent() = default;
	HighScoreEntryComponent(const HighScoreEntryComponent& other) = delete;
	HighScoreEntryComponent(HighScoreEntryComponent&& other) = delete;
	HighScoreEntryComponent& operator=(const HighScoreEntryComponent& other) = delete;
	HighScoreEntryComponent& operator=(HighScoreEntryComponent&& other) = delete;
private:
	void CreateNumberText(int number);
	void CreateScoreText(int Score);
	void CreateInitialsText(const std::string& initials);

	std::shared_ptr<bew::Font> m_Font;
	SDL_Color m_Color;
};

