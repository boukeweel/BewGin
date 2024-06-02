#include "CaptureBeamComponent.h"

#include "AnimatorComponent.h"
#include "GameObject.h"
#include "GameTime.h"
#include "SpriteSheetComponent.h"

CaptureBeamComponent::CaptureBeamComponent(bew::GameObject* pParentObject) : Component(pParentObject)
{
}

void CaptureBeamComponent::Update()
{
	if(m_StartCapturing)
	{
		m_timer += bew::GameTime::GetDeltaTimeFloat();
		m_SegmentTime += bew::GameTime::GetDeltaTimeFloat();

		float segmentDuration = (m_TotalBeamTime -  m_WaitTime) / static_cast<float>(m_Segments * 2);

		if(m_SegmentTime >= segmentDuration)
		{
			m_SegmentTime -= segmentDuration;

			if (m_Increasing) {
				m_SpritePart += 1.0f / m_Segments; 
				if (m_SpritePart >= 1.0f) {
					m_SpritePart = 1.0f; 
					m_Increasing = false;
					m_SegmentTime -= m_WaitTime;
				}
			}
			else {
				m_SpritePart -= 1.0f / m_Segments; 
				if (m_SpritePart <= 0.0f) {
					m_SpritePart = 0.0f; 
					m_Increasing = true;
				}
			}

			GetParentObject()->GetComponent<bew::SpriteSheetComponent>()->SetSpriteSize({ 1,m_SpritePart });
		}

		if(m_timer >= m_TotalBeamTime)
		{
			m_StartCapturing = false;
			m_Finished = true;
		}

	}
}


void CaptureBeamComponent::ResetBeam()
{
	GetParentObject()->GetComponent<bew::AnimatorComponent>()->StopCurrentAnimation();
	m_timer = 0;
	GetParentObject()->GetComponent<bew::SpriteSheetComponent>()->SetSpriteSize({ 1,0 });
	m_Finished = false;
	m_SpritePart = 0;
}

void CaptureBeamComponent::StartCapturing()
{
	ResetBeam();
	m_StartCapturing = true;
	GetParentObject()->GetComponent<bew::AnimatorComponent>()->PlayCurrentAmation();
}
