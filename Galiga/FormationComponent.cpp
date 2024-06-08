#include "FormationComponent.h"

#include "EnemyComponent.h"
#include "GameObject.h"
#include "GameTime.h"


FormationComponent::FormationComponent(bew::GameObject* pParentObject) : Component(pParentObject)
{
}

void FormationComponent::Lock()
{
    if(m_Locked)
        return;

    m_AmountEnemies--;
    if(m_AmountEnemies == 0)
    {
        m_Locked = true;
    }
}

void FormationComponent::Unlock()
{
    m_Locked = false;
}

void FormationComponent::Update()
{
    Moving();
}

void FormationComponent::Moving()
{
    //moving before all enemys are in postion
    if (!m_Locked || m_OffsetCounter != 4)
    {
        m_OffsetTimer += bew::GameTime::GetDeltaTimeFloat();
        if (m_OffsetTimer >= m_OffsetDelay)
        {
            m_OffsetCounter++;

            glm::vec3 Direction{ -1,0,0 };

            GetParentObject()->Translate(Direction * static_cast<float>(m_OffsetDirection) * m_OffsetAmount);

            if (m_OffsetCounter == 8)
            {
                m_OffsetCounter = 0;
                m_OffsetDirection *= -1;
            }

            m_OffsetTimer = 0.f;
        }
    }
}