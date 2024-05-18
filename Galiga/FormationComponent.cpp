#include "FormationComponent.h"

#include <iostream>

#include "EnemyComponent.h"
#include "fstream"
#include "GameObject.h"
#include "GameTime.h"
#include "ObjectPreset.h"
#include "RandomFunctions.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"

FormationComponent::FormationComponent(bew::GameObject* pParentObject, const std::string& FileName) : Component(pParentObject)
{
    LoadFormationFile(FileName);
}

void FormationComponent::Lock()
{
    m_AmountEnemies--;
    if(m_AmountEnemies == 0)
    {
        m_Locked = true;
    }
}

void FormationComponent::Update()
{
    Breathing();
    SpawnEnemies();
}

void FormationComponent::Breathing()
{
    //breathing animation
    if (m_Locked || m_OffsetCounter != 4)
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

void FormationComponent::SpawnEnemies()
{
    if(m_Enemies.size() != 0)
    {
        m_TimeWave += bew::GameTime::GetDeltaTimeFloat();
        if(m_TimeWave >= m_WaveDelay && !m_SpawningWave)
        {
            m_SpawningWave = true;

            if (m_RandomPath == 0)
                m_RandomPath = 1;
            else
            {
                m_RandomPath = 0;
            }

            m_TimeWave = 0;
            
        }
       
        if (m_SpawningWave)
        {
            m_TimeDelay += bew::GameTime::GetDeltaTimeFloat();
            if(m_TimeDelay >= m_SpawnDelay)
            {
                const int enemyCount = static_cast<int>(m_Enemies.size());
                int RandomEnemy = bew::RandomFunctions::RandomI(0, enemyCount - 1);
                auto comp = m_Enemies[RandomEnemy]->GetComponent<EnemyComponent>();
                comp->SetPath(m_RandomPath);
                comp->StartAndSetActive();
                m_Enemies.erase(m_Enemies.begin() + RandomEnemy);

                m_EnemiesSpawnedThisWave++;
                m_TimeDelay = 0;

                if(m_EnemiesSpawnedThisWave == m_EnemiesInOneWave)
                {
                    m_EnemiesSpawnedThisWave = 0;
                    m_SpawningWave = false;
                }
            }
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
                AddbutterFly({ x,y,0 });
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

    m_AmountEnemies = static_cast<int>(m_Enemies.size());
}

void FormationComponent::AddBoss(glm::vec3 pos)
{
    BossEnemyPreset BossPreset;

    auto Boss = BossPreset.Create();
    auto EnemyComp = Boss->GetComponent<EnemyComponent>();
    EnemyComp->SetFormationPosition(this, pos);

    Boss->SetIsActive(false);

    m_Enemies.emplace_back(Boss.get());

    bew::SceneManager::GetInstance().GetCurrentScene().Add(std::move(Boss));
}

void FormationComponent::AddBee(glm::vec3 pos)
{
    BeeEnemyPreset beePreset;

    auto bee = beePreset.Create();
    auto EnemyComp = bee->GetComponent<EnemyComponent>();
    EnemyComp->SetFormationPosition(this,pos);

    bee->SetIsActive(false);

    m_Enemies.emplace_back(bee.get());
    bew::SceneManager::GetInstance().GetCurrentScene().Add(std::move(bee));

}
void FormationComponent::AddbutterFly(glm::vec3 pos)
{
    ButterfliesEnemyPreset butterfliesPreset;

    auto butterFly = butterfliesPreset.Create();
    auto EnemyComp = butterFly->GetComponent<EnemyComponent>();
    EnemyComp->SetFormationPosition(this, pos);

    butterFly->SetIsActive(false);

    m_Enemies.emplace_back(butterFly.get());

    bew::SceneManager::GetInstance().GetCurrentScene().Add(std::move(butterFly));
}




