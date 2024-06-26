#include "CaptureBeamComponent.h"

#include <SDL_rect.h>

#include "AnimatorComponent.h"
#include "GameEntityData.h"
#include "GameObject.h"
#include "GameTime.h"
#include "HealthComponent.h"
#include "HitBoxComponent.h"
#include "PlayerComponent.h"
#include "SoundServiceLocator.h"
#include "SpriteSheetComponent.h"
#include "SubjectComponent.h"

CaptureBeamComponent::CaptureBeamComponent(bew::GameObject* pParentObject) : Component(pParentObject)
{
	m_pPlayers = GameEntityData::GetInstance().GetPlayers();
}

void CaptureBeamComponent::Update()
{
	if(m_StartCapturing)
	{
		m_timer += bew::GameTime::GetDeltaTimeFloat();
		m_SegmentTime += bew::GameTime::GetDeltaTimeFloat();

		float segmentDuration = (m_TotalBeamTime -  m_WaitTime) / static_cast<float>(m_Segments * 2);
		auto hitboxComp = GetParentObject()->GetComponent<bew::HitBoxComponent>();

		if(m_SegmentTime >= segmentDuration)
		{
			m_SegmentTime -= segmentDuration;
			SDL_Rect hitbox = hitboxComp->GetHitBoxRaw();
			if (m_Increasing) {
				m_SpritePart += 1.0f / m_Segments;
				//bad Magic number
				hitboxComp->SetHitBox({ hitbox.x, hitbox.y, hitbox.w, hitbox.h + 32 });

				if (m_SpritePart >= 1.0f) {
					m_SpritePart = 1.0f; 
					m_Increasing = false;
					m_SegmentTime -= m_WaitTime;

					if (!m_Captured)
						bew::SoundServiceLocator::GetSoundSystem().Play(7, 2);
				}
			}
			else {
				//bad Magic number
				hitboxComp->SetHitBox({ hitbox.x, hitbox.y, hitbox.w, hitbox.h - 32 });
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
			m_SpritePart = 0.0f;
			m_Increasing = true;
		}

	}
}

void CaptureBeamComponent::FixedUpdate()
{
	Collision();
}


void CaptureBeamComponent::ResetBeam()
{
	GetParentObject()->GetComponent<bew::AnimatorComponent>()->StopCurrentAnimation();
	m_timer = 0;
	GetParentObject()->GetComponent<bew::SpriteSheetComponent>()->SetSpriteSize({ 1,0 });
	m_Finished = false;
	m_Increasing = true;
	m_Captured = false;
	m_PlayedCaptureSound = false;
	m_SpritePart = 0;
}

void CaptureBeamComponent::StartCapturing()
{
	ResetBeam();
	m_StartCapturing = true;
	GetParentObject()->GetComponent<bew::AnimatorComponent>()->PlayCurrentAmation();
	bew::SoundServiceLocator::GetSoundSystem().Play(6, 2);
}

void CaptureBeamComponent::Collision()
{
	//should be in the player
	for (const auto& Player : *m_pPlayers)
	{
		if (Player->GetIsActive())
		{
			if (GetParentObject()->GetComponent<bew::HitBoxComponent>()->InsideHitBox(Player))
			{
				Player->GetComponent<PlayerComponent>()->StartSuckUpAnimation(GetParentObject());
				//only play sound once
				if(!m_PlayedCaptureSound)
				{
					bew::SoundServiceLocator::GetSoundSystem().Play(8, 5);
					m_PlayedCaptureSound = true;
				}
					
				m_Captured = true;
			}
		}
	}
}
