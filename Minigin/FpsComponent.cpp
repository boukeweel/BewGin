#include "FpsComponent.h"

#include <iomanip>
#include <sstream>

#include "GameObject.h"
#include "TextComponent.h"

dae::FpsComponent::FpsComponent(GameObject* pParentObject) :  Component(pParentObject),m_fps{0},m_FrameCount{0},m_AccumulatedTime{0},m_UpdateInterval{0.5f}
{
	if(GetParentObject()->HasComponent<TextComponent>())
	{
		m_pTextComponent = GetParentObject()->GetComponent<TextComponent>();
	}
}

void dae::FpsComponent::Update(float deltaTime)
{
    m_AccumulatedTime += deltaTime;
    m_FrameCount++;

    if (m_AccumulatedTime >= m_UpdateInterval) {
        
        m_fps = m_FrameCount / m_AccumulatedTime;

        std::ostringstream stream;
        stream << std::fixed << std::setprecision(1) << m_fps;
        m_pTextComponent->SetText(stream.str());

        m_FrameCount = 0;
        m_AccumulatedTime = 0;
    }
}
