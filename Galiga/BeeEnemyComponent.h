#pragma once
#include "EnemyComponent.h"
class BeeEnemyComponent :
    public EnemyComponent
{

public:
    static void CreateAttackingPaths();

    BeeEnemyComponent(bew::GameObject* pParentObject);

    std::vector<glm::vec2>* GetAttackingPath(int index) const override { return &s_AttackingPaths[index]; }

    virtual ~BeeEnemyComponent() override = default;
    BeeEnemyComponent(const BeeEnemyComponent& other) = delete;
    BeeEnemyComponent(BeeEnemyComponent&& other) = delete;
    BeeEnemyComponent& operator=(const BeeEnemyComponent& other) = delete;
    BeeEnemyComponent& operator=(BeeEnemyComponent&& other) = delete;
private:
    void TakeDamages(bew::GameObject* pPlayer) override;

    static std::vector<std::vector<glm::vec2>> s_AttackingPaths;
};

