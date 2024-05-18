#include "FormationComponent.h"

#include <iostream>

#include "fstream"
#include "GameObject.h"
#include "GameTime.h"
#include "ResourceManager.h"

FormationComponent::FormationComponent(bew::GameObject* pParentObject, const std::string& FileName) : Component(pParentObject)
{
    LoadFormationFile(FileName);
}

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

void FormationComponent::LoadFormationFile(const std::string& FileName)
{
	std::ifstream file = bew::ResourceManager::GetInstance().LoadTxtFile(FileName);

	if (!file)
	{
		std::cout << "file does not exist " << FileName << "\n";
		return;
	}

    char ch;
    int x = 0, y = 0;

    while (file.get(ch)) {
        if (ch == '\n') {
            y++;
            x = 0;
        }
        else {
            switch (ch) {
            case '-':
                break;
            case 'o':
                AddBoss({ x,y,0 });
                break;
            case 'v':
                Addbutterfly({ x,y,0 });
                break;
            case 'b':
                AddBee({ x,y,0 });
                break;
            default:
                std::cout << "Unknown character found: " << ch << " at (" << x << ", " << y << ")" << std::endl;
                break;
            }
            x++;
        }
    }


}

void FormationComponent::AddBoss(glm::vec3 /*pos*/)
{

}

void FormationComponent::AddBee(glm::vec3 /*pos*/)
{
	
}
void FormationComponent::Addbutterfly(glm::vec3 /*pos*/)
{
	
}



