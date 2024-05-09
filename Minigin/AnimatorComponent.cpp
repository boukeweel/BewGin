#include "AnimatorComponent.h"

bew::AnimatorComponent::AnimatorComponent(GameObject* pParentObject):Component(pParentObject)
{
}

void bew::AnimatorComponent::Update()
{
	animations[m_CurrentAnimation]->Update();
}

void bew::AnimatorComponent::SwitchAnimation(int animation)
{
	m_CurrentAnimation = animation;
}

void bew::AnimatorComponent::AddAnimation(std::unique_ptr<Animation> animation)
{
	animations.emplace_back(std::move(animation));
}

void bew::AnimatorComponent::PlayCurrentAmation()
{
	animations[m_CurrentAnimation]->PlayAnimation();
}

void bew::AnimatorComponent::StopCurrentAnimation()
{
	animations[m_CurrentAnimation]->StopAnimation();
}


bew::Animation* bew::AnimatorComponent::getCurrentAnimation()
{
	return animations[m_CurrentAnimation].get();
}
