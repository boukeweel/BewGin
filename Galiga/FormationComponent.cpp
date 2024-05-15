#include "FormationComponent.h"

#include "GameObject.h"
#include "GameTime.h"

FormationComponent::FormationComponent(bew::GameObject* pParentObject) : Component(pParentObject)
{}

void FormationComponent::Update()
{
	//breathing animation
	if(m_Locked || m_OffsetCounter != 4)
	{
		m_OffsetTimer += bew::GameTime::GetDeltaTimeFloat();
		if(m_OffsetTimer >= m_OffsetDelay)
		{
			m_OffsetCounter++;

			glm::vec3 Direction{ -1,0,0 };

			GetParentObject()->Translate(Direction * static_cast<float>(m_OffsetDirection) * m_OffsetAmount);

			if(m_OffsetCounter == 8)
			{
				m_OffsetCounter = 0;
				m_OffsetDirection *= -1;
			}

			m_OffsetTimer = 0.f;
		}

	}
}

