#include "FpsComponent.h"

#include "TextComponent.h"

dae::FpsComponent::FpsComponent(Transform& transform, TextComponent* textComponent) :  Component(transform), textComponent{ textComponent },m_fps{0}
{
}

dae::FpsComponent::~FpsComponent()
{
	delete textComponent;
}

void dae::FpsComponent::Update(float deltaTime)
{
	m_fps = 1.0f / deltaTime;

	textComponent->SetText(std::to_string(m_fps));
}
