#pragma once
#include "EnemyComponent.h"
class BossEnemyComponent :
    public EnemyComponent
{
public:
    BossEnemyComponent(bew::GameObject* pParentObject);

private:
    void TakeDamages(bew::GameObject* pPlayer) override;

    int m_AmountPoints{ 100 };
};

