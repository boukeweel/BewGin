#pragma once
#include <Component.h>
#include <vector>

class EnemyAttackControllerComponent :
    public bew::Component
{
public:
    EnemyAttackControllerComponent(bew::GameObject* pParentObject);

    void Update() override;

    void StartDisabledTime() { m_StartDisabledTimer = true; }

    ~EnemyAttackControllerComponent() override = default;
    EnemyAttackControllerComponent(const EnemyAttackControllerComponent& other) = delete;
    EnemyAttackControllerComponent(EnemyAttackControllerComponent&& other) = delete;
    EnemyAttackControllerComponent& operator=(const EnemyAttackControllerComponent& other) = delete;
    EnemyAttackControllerComponent& operator=(EnemyAttackControllerComponent&& other) = delete;

private:
    void EnemyAttacking();
    void DisabledTime();
    void CheckAllEnemiesDead() const;
    bew::GameObject* SelectRandomEnemy() const;

    std::vector<bew::GameObject*>* m_pEnemies;

    float m_Timer{};
    const float m_EnemyAttackDelay{ 1.f };

    bool m_StartDisabledTimer{ false };
    float m_DisabledTimer{};
    const float m_DisabledTime{ 5.f };
};

