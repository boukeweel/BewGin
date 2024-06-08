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
    FormationComponent(bew::GameObject* pParentObject);
    
    glm::vec2 GetGridSize() const { return m_GridSize; }

    void Update() override;

    void Lock();
    void Unlock();
    bool GetIsLocked() const { return m_Locked && m_OffsetCounter == 4; }

    void SetAmountEnemies(int amount) { m_AmountEnemies = amount; }

    ~FormationComponent() override = default;
    FormationComponent(const FormationComponent& other) = delete;
    FormationComponent(FormationComponent&& other) = delete;
    FormationComponent& operator=(const FormationComponent& other) = delete;
    FormationComponent& operator=(FormationComponent&& other) = delete;

private:
    void Moving();

    //For Moving Formation side to side
    float m_OffsetAmount{10.f};
    float m_OffsetTimer{0.f};
    float m_OffsetDelay{0.4f};
    int m_OffsetCounter{4};
    int m_OffsetDirection{1};

    glm::vec2 m_GridSize{32.f,32.f};
    bool m_Locked{false};

    int m_AmountEnemies{};
};

