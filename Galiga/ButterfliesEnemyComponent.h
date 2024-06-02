#pragma once
#include "EnemyComponent.h"
class ButterfliesEnemyComponent :
    public EnemyComponent
{
public:
    static void CreateAttackingPaths();

    ButterfliesEnemyComponent(bew::GameObject* pParentObject);

    std::vector<glm::vec2>* GetAttackingPath(int index) const override { return &s_AttackingPaths[index]; }


    virtual ~ButterfliesEnemyComponent() override = default;
    ButterfliesEnemyComponent(const ButterfliesEnemyComponent& other) = delete;
    ButterfliesEnemyComponent(ButterfliesEnemyComponent&& other) = delete;
    ButterfliesEnemyComponent& operator=(const ButterfliesEnemyComponent& other) = delete;
    ButterfliesEnemyComponent& operator=(ButterfliesEnemyComponent&& other) = delete;
private:
    void TakeDamages(bew::GameObject* pPlayer) override;

    int m_AmountPoints{ 100 };

    static std::vector<std::vector<glm::vec2>> s_AttackingPaths;
};

