#include "EnemySpawnerComponent.h"

#include <iostream>

#include "EnemyComponent.h"
#include "fstream"

#include "GameEntityData.h"
#include "GameTime.h"
#include "ObjectPreset.h"
#include "PoolComponent.h"
#include "RandomFunctions.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"


EnemySpawnerComponent::EnemySpawnerComponent(bew::GameObject* pParentObject):Component(pParentObject)
{
}

void EnemySpawnerComponent::AddLevel(const std::string& levelName)
{
    m_levels.emplace_back(levelName);
}
void EnemySpawnerComponent::NextLevel()
{
    m_CurrentLevel++;

    if(m_CurrentLevel > static_cast<int>(m_levels.size()))
    {
        m_CurrentLevel = 0;
    }

    m_EnemiesSpawnedThisWave = 0;
    m_TimeWave = 0;
    m_SpawningWave = false;
    m_TimeDelay = 0;

    GetParentObject()->GetComponent<FormationComponent>()->Unlock();

    LoadFormationFile();
}



void EnemySpawnerComponent::Update()
{
    SpawnEnemies();
}

void EnemySpawnerComponent::SpawnEnemies()
{
    if (m_Enemies.size() != 0)
    {
        m_TimeWave += bew::GameTime::GetDeltaTimeFloat();
        if (m_TimeWave >= m_WaveDelay && !m_SpawningWave)
        {
            m_SpawningWave = true;

            m_ChosenPath = (m_ChosenPath + 1) % 4;

            m_TimeWave = 0;

        }

        if (m_SpawningWave)
        {
            m_TimeDelay += bew::GameTime::GetDeltaTimeFloat();
            if (m_TimeDelay >= m_SpawnDelay)
            {
                const int enemyCount = static_cast<int>(m_Enemies.size());
                int RandomEnemy = bew::RandomFunctions::RandomI(0, enemyCount - 1);
                auto comp = m_Enemies[RandomEnemy]->GetComponent<EnemyComponent>();
                comp->SetForamationPath(m_ChosenPath);
                comp->StartAndSetActive();
                m_Enemies.erase(m_Enemies.begin() + RandomEnemy);

                m_EnemiesSpawnedThisWave++;
                m_TimeDelay = 0;

                if (m_EnemiesSpawnedThisWave == m_EnemiesInOneWave)
                {
                    m_EnemiesSpawnedThisWave = 0;
                    m_SpawningWave = false;
                }
            }
        }
    }
}

void EnemySpawnerComponent::LoadFormationFile()
{
    std::ifstream file = bew::ResourceManager::GetInstance().LoadTxtFileIf(m_levels[m_CurrentLevel]);

    if (!file)
    {
        std::cout << "file does not exist " << m_levels[m_CurrentLevel] << "\n";
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
                AddButterFly({ x,y,0 });
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
    GetParentObject()->GetComponent<FormationComponent>()->SetAmountEnemies(static_cast<int>(m_Enemies.size()));
    GameEntityData::GetInstance().AddEnemies(m_Enemies);
}

void EnemySpawnerComponent::AddBoss(glm::vec3 pos)
{
    bew::GameObject* SelectBoss = nullptr;
    for (auto boss : m_Bosses)
    {
        if (!boss->GetComponent<PoolComponent>()->InUse())
        {
            SelectBoss = boss;
            break;
        }
    }

    if (!SelectBoss)
    {
        BossEnemyPreset BossPreset;
        auto Boss = BossPreset.Create();
        SetupEnemy(Boss.get(), pos);

        m_Bosses.emplace_back(Boss.get());

        bew::SceneManager::GetInstance().GetCurrentScene().Add(std::move(Boss));
    }
    else
    {
        SetupEnemy(SelectBoss, pos);
    }
   
  
}

void EnemySpawnerComponent::AddBee(glm::vec3 pos)
{
    bew::GameObject* SelectBee = nullptr;
    for (auto bee : m_Bees)
    {
        if (!bee->GetComponent<PoolComponent>()->InUse())
        {
            SelectBee = bee;
            break;
        }
    }

    if (!SelectBee)
    {
        BeeEnemyPreset beePreset;
        auto bee = beePreset.Create();
        SetupEnemy(bee.get(), pos);

        m_Bees.emplace_back(bee.get());

        bew::SceneManager::GetInstance().GetCurrentScene().Add(std::move(bee));
    }
    else
    {
        SetupEnemy(SelectBee, pos);
    }
}

void EnemySpawnerComponent::AddButterFly(glm::vec3 pos)
{
    bew::GameObject* SelectButterfly = nullptr;
    for (auto butterFly : m_ButterFlies)
    {
        if (!butterFly->GetComponent<PoolComponent>()->InUse())
        {
            SelectButterfly = butterFly;
            break;
        }
    }

    if (!SelectButterfly)
    {
        ButterfliesEnemyPreset butterfliesPreset;
        auto butterFly = butterfliesPreset.Create();
        SetupEnemy(butterFly.get(), pos);

        m_ButterFlies.emplace_back(butterFly.get());

        bew::SceneManager::GetInstance().GetCurrentScene().Add(std::move(butterFly));
    }
    else
    {
        SetupEnemy(SelectButterfly, pos);
    }
}

void EnemySpawnerComponent::SetupEnemy(bew::GameObject* enemy, const glm::vec3& pos)
{
    auto EnemyComp = enemy->GetComponent<EnemyComponent>();
    EnemyComp->SetFormationPosition(GetParentObject()->GetComponent<FormationComponent>(), pos);
    enemy->GetComponent<PoolComponent>()->SetInUse(true);
    if (pos.x <= 5)
        EnemyComp->SetAttackSide(0);
    else
        EnemyComp->SetAttackSide(1);
    enemy->SetIsActive(false);
    enemy->SetParrent(nullptr);
    EnemyComp->ResetEnemy();

    m_Enemies.emplace_back(enemy);
}




