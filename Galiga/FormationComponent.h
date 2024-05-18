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
    void Lock() { m_Locked = true; }

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

    glm::vec2 m_GridSize{32.f,32.f};

    std::vector<std::unique_ptr<bew::GameObject>> m_Enemies;

    bool m_Locked{false};
};

