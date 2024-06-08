#pragma once
#include "CaptureBeamComponent.h"
#include "EnemyComponent.h"
class BossEnemyComponent :
    public EnemyComponent
{
public:
    static void CreateAttackingPaths();

    BossEnemyComponent(bew::GameObject* pParentObject,CaptureBeamComponent* captureBeam);
    void ResetEnemy() override;

    std::vector<glm::vec2>* GetAttackingPath(int index) const override { return &s_AttackingPaths[index]; }

    CaptureBeamComponent* GetCaptureBeam() const override { return m_CaptureBeam; }

    void SetAbleToAttack(bool ableToAttack) override;

    virtual ~BossEnemyComponent() override = default;
    BossEnemyComponent(const BossEnemyComponent& other) = delete;
    BossEnemyComponent(BossEnemyComponent&& other) = delete;
    BossEnemyComponent& operator=(const BossEnemyComponent& other) = delete;
    BossEnemyComponent& operator=(BossEnemyComponent&& other) = delete;
private:
    void TakeDamages(bew::GameObject* pPlayer) override;

    static std::vector<std::vector<glm::vec2>> s_AttackingPaths;

    CaptureBeamComponent* m_CaptureBeam;
};

