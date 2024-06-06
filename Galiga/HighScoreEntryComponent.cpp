#include "HighScoreEntryComponent.h"

#include <memory>
#include <memory>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"

HighScoreEntryComponent::HighScoreEntryComponent(bew::GameObject* pParentOjbect) :Component(pParentOjbect)
{
	m_Font = bew::ResourceManager::GetInstance().LoadFont("PressStart2P-Regular.ttf", 14);
}

void HighScoreEntryComponent::CreateTextObjects(int number, int score, const std::string& initials)
{
    SetColor(number);
	CreateNumberText(number);
	CreateScoreText(score);
	CreateInitialsText(initials);
}

void HighScoreEntryComponent::ChanceEnteryValues(int number, int score, const std::string& initials)
{
    SetColor(number);
    GetParentObject()->GetChildAtIndex(0)->GetComponent<bew::TextComponent>()->SetText("NO. " + std::to_string(number));
    GetParentObject()->GetChildAtIndex(1)->GetComponent<bew::TextComponent>()->SetText(std::to_string(score));
    GetParentObject()->GetChildAtIndex(2)->GetComponent<bew::TextComponent>()->SetText(initials);
}

void HighScoreEntryComponent::CreateNumberText(int number)
{
	auto NumberTxt = std::make_unique<bew::GameObject>();
    NumberTxt->SetPosition(0, 0);
   
    NumberTxt->AddComponent<bew::TextComponent>("NO. " + std::to_string(number), m_Font,m_Color);
    NumberTxt->SetParrent(GetParentObject());

    bew::SceneManager::GetInstance().AddToCurrentScene(std::move(NumberTxt));

}

void HighScoreEntryComponent::CreateScoreText(int Score)
{
    auto ScoreTxt = std::make_unique<bew::GameObject>();
    ScoreTxt->SetPosition(120, 0);

    ScoreTxt->AddComponent<bew::TextComponent>(std::to_string(Score), m_Font, m_Color);
    ScoreTxt->SetParrent(GetParentObject());

    bew::SceneManager::GetInstance().AddToCurrentScene(std::move(ScoreTxt));
}

void HighScoreEntryComponent::CreateInitialsText(const std::string& initials)
{
    auto InitialsTxt = std::make_unique<bew::GameObject>();
    InitialsTxt->SetPosition(250, 0);

    InitialsTxt->AddComponent<bew::TextComponent>(initials, m_Font, m_Color);
    InitialsTxt->SetParrent(GetParentObject());

    bew::SceneManager::GetInstance().AddToCurrentScene(std::move(InitialsTxt));
}

void HighScoreEntryComponent::SetColor(int number)
{
    switch (number)
    {
    case 1:
        m_Color = { 255, 0, 0, 255 }; // Red
        break;
    case 2:
        m_Color = { 255, 192, 203, 255 }; // Pink
        break;
    case 3:
    case 4:
        m_Color = { 255, 255, 0, 255 }; // Yellow
        break;
    case 5:
    case 6:
        m_Color = { 0, 255, 0, 255 }; // Green
        break;
    case 7:
    case 8:
        m_Color = { 0, 255, 255, 255 }; // Blue
        break;
    default:
        m_Color = { 255, 255, 255, 255 }; // Default color (white)
        break;
    }

}
