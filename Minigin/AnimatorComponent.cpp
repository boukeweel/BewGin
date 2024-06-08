#include "AnimatorComponent.h"

bew::AnimatorComponent::AnimatorComponent(GameObject* pParentObject):Component(pParentObject)
{
}

void bew::AnimatorComponent::Update()
{
	m_pAnimations[m_CurrentAnimation]->Update();
}

void bew::AnimatorComponent::SwitchAnimation(int animation,bool PlayAnimation)
{
	m_CurrentAnimation = animation;
	if (PlayAnimation)
		PlayCurrentAmation();
}

void bew::AnimatorComponent::AddAnimation(std::unique_ptr<Animation> animation)
{
	m_pAnimations.emplace_back(std::move(animation));
}

void bew::AnimatorComponent::PlayCurrentAmation()
{
	m_pAnimations[m_CurrentAnimation]->PlayAnimation();
}

void bew::AnimatorComponent::StopCurrentAnimation()
{
	m_pAnimations[m_CurrentAnimation]->StopAnimation();
}

bew::Animation* bew::AnimatorComponent::getCurrentAnimation()
{
	return m_pAnimations[m_CurrentAnimation].get();
}
