#include "FpsComponent.h"

#include <iomanip>
#include <sstream>

#include "GameObject.h"
#include "TextComponent.h"

dae::FpsComponent::FpsComponent(GameObject* pParentObject) :  Component(pParentObject),m_fps{0},m_frameCount{0},m_accumulatedTime{0},m_updateInterval{0.5f}
{
	if(GetParentObject()->HasComponent<TextComponent>())
	{
		textComponent = GetParentObject()->GetComponent<TextComponent>();
	}
}

dae::FpsComponent::~FpsComponent()
{
	delete textComponent;
    
}

void dae::FpsComponent::Update(float deltaTime)
{
    m_accumulatedTime += deltaTime;
    m_frameCount++;

    if (m_accumulatedTime >= m_updateInterval) {
        
        m_fps = m_frameCount / m_accumulatedTime;

        std::ostringstream stream;
        stream << std::fixed << std::setprecision(1) << m_fps;
        textComponent->SetText(stream.str());

        m_frameCount = 0;
        m_accumulatedTime = 0;
    }
}
