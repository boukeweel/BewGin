#include "InitialsComponent.h"

#include <iostream>

#include "GameData.h"
#include "GameObject.h"
#include "GameTime.h"
#include "TextComponent.h"

InitialsComponent::InitialsComponent(bew::GameObject* pParentOjbect, bool Player1) : Component(pParentOjbect),m_Player1{Player1}
{
    m_Initials[0] = 'A';
    m_Initials[1] = 'A';
    m_Initials[2] = 'A';
}

void InitialsComponent::Update()
{
    m_timer += bew::GameTime::GetDeltaTimeFloat();
    if (m_Visible && m_timer >= m_VisibleTime)
    {
        m_Visible = false;
        m_timer = 0.0f;
        UpdateText();
    }
    else if (!m_Visible && m_timer >= m_DisappearTime)
    {
        m_Visible = true;
        m_timer = 0.0f;
        UpdateText();
    }
}

void InitialsComponent::Select()
{
    m_Initials[m_CurrentSelected]++;
    if (m_Initials[m_CurrentSelected] > 'Z')
    {
        m_Initials[m_CurrentSelected] = 'A';
    }
    m_timer = 0;
    SetText();
}

void InitialsComponent::MoveLeft()
{
    if (m_CurrentSelected > 0)
    {
        m_CurrentSelected--;
    }
    else
    {
        m_CurrentSelected = 2;
    }
}

void InitialsComponent::MoveRight()
{
    if (m_CurrentSelected < 2)
    {
        m_CurrentSelected++;
    }
    else
    {
        m_CurrentSelected = 0;
    }
}

void InitialsComponent::Finish()
{
    if(m_AddedScore)
        return;
    std::string initialsString(m_Initials, 3);
    if(m_Player1)
    {
        GameData::GetInstance().WriteToLeadBoard(GameData::GetInstance().GetCurrentScoreP1(), initialsString);
    }
    else
    {
        GameData::GetInstance().WriteToLeadBoard(GameData::GetInstance().GetCurrentScoreP2(), initialsString);
    }
    m_AddedScore = true;
}

void InitialsComponent::SetText()
{
    std::string initialsString(m_Initials, 3);
    GetParentObject()->GetComponent<bew::TextComponent>()->SetText(initialsString);
}

void InitialsComponent::UpdateText()
{
    std::string displayText = { m_Initials[0], m_Initials[1], m_Initials[2] };
    if (!m_Visible)
    {
        displayText[m_CurrentSelected] = ' ';
    }

    auto textComponent = GetParentObject()->GetComponent<bew::TextComponent>();
    if (textComponent)
    {
        textComponent->SetText(displayText);
    }
}
