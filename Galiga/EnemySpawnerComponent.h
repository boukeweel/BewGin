#pragma once
#include <Component.h>
#include <string>
#include <vector>

#include "FormationComponent.h"

class EnemySpawnerComponent :
    public bew::Component
{
public:
    EnemySpawnerComponent(bew::GameObject* pParentObject);

    void Update() override;
    void AddLevel(const std::string& levelName);
    void NextLevel();

    ~EnemySpawnerComponent() override = default;
    EnemySpawnerComponent(const EnemySpawnerComponent& other) = delete;
    EnemySpawnerComponent(EnemySpawnerComponent&& other) = delete;
    EnemySpawnerComponent& operator=(const EnemySpawnerComponent& other) = delete;
    EnemySpawnerComponent& operator=(EnemySpawnerComponent&& other) = delete;

private:
    void LoadFormationFile();
    void AddBoss(glm::vec3 pos);
    void AddBee(glm::vec3 pos);
    void AddButterFly(glm::vec3 pos);

    void SetupEnemy(bew::GameObject* enemy, const glm::vec3& pos);

    void SpawnEnemies();

    std::vector<std::string> m_levels;
    int m_CurrentLevel{0};

    float m_WaveDelay{ 1.f };
    float m_TimeWave{};
    float m_SpawnDelay{ 0.1f };
    float m_TimeDelay{};
    int m_EnemiesInOneWave{ 6 };
    int m_EnemiesSpawnedThisWave{};
    int m_ChosenPath{};
    bool m_SpawningWave{ false };

    std::vector<bew::GameObject*> m_Enemies;

    std::vector<bew::GameObject*> m_Bees;
    std::vector<bew::GameObject*> m_ButterFlies;
    std::vector<bew::GameObject*> m_Bosses;
};

