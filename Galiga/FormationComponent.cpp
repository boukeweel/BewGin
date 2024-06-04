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
    Breathing();
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
void FormationComponent::Breathing()
{
    //breathing
    //todo this looks weird if time fix it if not just delete it
   /* if(m_Locked)
    {
        m_SpreadTimer += bew::GameTime::GetDeltaTimeFloat();
        if(m_SpreadTimer >= m_SpreadDelay)
        {
            m_SpreadCounter += m_SpreadDirection;

            float spread = static_cast<float>(m_SpreadDirection * ((m_SpreadCounter % 2 == 0) ? 1 : 2));

            m_GridSize.x += spread;

            glm::vec3 position = GetParentObject()->GetWorldPosition() ;
            position.x -= spread * 5;
            GetParentObject()->SetPosition(position);

            if(m_SpreadCounter == 4 || m_SpreadCounter == 0)
            {
                m_SpreadDirection *= -1;
            }
            m_SpreadTimer -= m_SpreadDelay;
        }
    }*/
}