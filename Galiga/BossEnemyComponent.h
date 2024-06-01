#pragma once
#include "EnemyComponent.h"
class BossEnemyComponent :
    public EnemyComponent
{
public:
    static void CreateAttackingPaths();

    BossEnemyComponent(bew::GameObject* pParentObject);

    std::vector<glm::vec2>* GetAttackingPath(int index) const override { return &s_AttackingPaths[index]; }

private:
    void TakeDamages(bew::GameObject* pPlayer) override;

    int m_AmountPoints{ 100 };

    static std::vector<std::vector<glm::vec2>> s_AttackingPaths;
};

