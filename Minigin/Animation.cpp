#include "Animation.h"
#include <iostream>
#include "GameObject.h"
#include "GameTime.h"
#include "SpriteSheetComponent.h"



bew::Animation::Animation(GameObject* pParentObject, const std::vector<KeyFrame>& keyframes, double frameDuration,bool looping)
	: Component(pParentObject),m_Keyframes(keyframes),m_FrameDuration{frameDuration},m_Looping{looping}
{
	m_pSpriteSheet = GetParentObject()->GetComponent<SpriteSheetComponent>();

	if (m_pSpriteSheet == nullptr)
	{
		std::cerr << "Please make sure a SpriteSheetComponent is on the Component \n";
	}
}

void bew::Animation::Update()
{
	if(m_IsAnimating && !m_Keyframes.empty())
	{
		m_TimeElapsed += GameTime::GetDeltaTime();
		if (m_TimeElapsed >= m_FrameDuration) {
			if (m_Looping)
			{
				m_CurrentFrame = (m_CurrentFrame + 1) % m_Keyframes.size();
			}
			else
			{
				m_CurrentFrame++;
				if (m_CurrentFrame == m_Keyframes.size() - 1)
					m_IsAnimating = false;
			}
			m_pSpriteSheet->SetSprite(m_Keyframes[m_CurrentFrame].row, m_Keyframes[m_CurrentFrame].column);
			m_TimeElapsed = 0.0;
		}
	}
}

void bew::Animation::SetKeyFrames(const std::vector<KeyFrame>& keyframes)
{
	m_Keyframes = keyframes;
}

void bew::Animation::SetFrameDuration(double frameDuration)
{
	m_FrameDuration = frameDuration;
}

void bew::Animation::PlayAnimation(const std::vector<KeyFrame>& keyframes, double frameDuration)
{
	m_Keyframes = keyframes;
	m_FrameDuration = frameDuration;
	m_CurrentFrame = 0;
	m_TimeElapsed = 0.0;
	m_IsAnimating = true;
}

void bew::Animation::PlayAnimation()
{
	m_CurrentFrame = 0;
	m_TimeElapsed = 0.0;
	m_IsAnimating = true;
}

void bew::Animation::StopAnimation()
{
	m_IsAnimating = false;
}
