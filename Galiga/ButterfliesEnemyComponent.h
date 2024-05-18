#pragma once
#include "EnemyComponent.h"
class ButterfliesEnemyComponent :
    public EnemyComponent
{
public:
    ButterfliesEnemyComponent(bew::GameObject* pParentObject);

private:
    void TakeDamages(bew::GameObject* pPlayer) override;

    int m_AmountPoints{ 100 };
};

