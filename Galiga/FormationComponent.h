#pragma once
#include <Component.h>
#include <memory>
#include <string>
#include <vector>

class EnemyComponent;

class FormationComponent :
    public bew::Component
{
public:
    FormationComponent(bew::GameObject* pParentObject, const std::string& FileName);
    
    glm::vec2 GetGridSize() const { return m_GridSize; }
    void Lock();
    void Update() override;

    ~FormationComponent() override = default;
    FormationComponent(const FormationComponent& other) = delete;
    FormationComponent(FormationComponent&& other) = delete;
    FormationComponent& operator=(const FormationComponent& other) = delete;
    FormationComponent& operator=(FormationComponent&& other) = delete;

private:

    void LoadFormationFile(const std::string& FileName);
    void AddBoss(glm::vec3 pos);
    void AddBee(glm::vec3 pos);
    void AddbutterFly(glm::vec3 pos);

    void Breathing();
    void SpawnEnemies();

    //For Moving Formation side to side
    float m_OffsetAmount{10.f};
    float m_OffsetTimer{0.f};
    float m_OffsetDelay{0.4f};
    int m_OffsetCounter{4};
    int m_OffsetDirection{1};

    float m_SpreadTimer{0.f};
    float m_SpreadDelay{1.f};
    int m_SpreadCounter{0};
    int m_SpreadDirection{1};

    //spawning timers
    float m_WaveDelay{1.f};
    float m_TimeWave;
    float m_SpawnDelay{0.15f};
    float m_TimeDelay;
    int m_EnemiesInOneWave{4};
    int m_EnemiesSpawnedThisWave{};
    int m_RandomPath{};
    bool m_SpawningWave{false};

    glm::vec2 m_GridSize{32.f,32.f};

    std::vector<bew::GameObject*> m_Enemies;

    bool m_Locked{false};
    int m_AmountEnemies;
};

