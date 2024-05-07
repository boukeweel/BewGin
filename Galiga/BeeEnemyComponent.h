#pragma once
#include "EnemyComponent.h"
class BeeEnemyComponent :
    public EnemyComponent
{
public:
    BeeEnemyComponent(bew::GameObject* pParentObject, bew::GameObject* Player);

    void Update() override;

    virtual ~BeeEnemyComponent() = default;

    BeeEnemyComponent(const BeeEnemyComponent& other) = delete;
    BeeEnemyComponent(BeeEnemyComponent&& other) = delete;
    BeeEnemyComponent& operator=(const BeeEnemyComponent& other) = delete;
    BeeEnemyComponent& operator=(BeeEnemyComponent&& other) = delete;

private:
    void Attack();
    void ShootingRun();
    void Crashing();
    void Returning();

    bool m_isBomming{ false };
};

