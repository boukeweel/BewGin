#pragma once
#include <Component.h>
#include <vector>

#include "CaptureBeamComponent.h"
#include "EnemyStates.h"


class FormationComponent;


//todo clean this class up it a mess
class EnemyComponent :
    public bew::Component
{
public:
    enum class EnemyTypes { Bee, Butterfly, Boss };

    static void CreatePaths();

    EnemyComponent(bew::GameObject* pParentObject);

    virtual void ResetEnemy();

    void FixedUpdate() override;
    void Update() override;
    void Render() const override;

    virtual void HandelStates();
    void StartAndSetActive();

    EnemyTypes GetEnemyType() const { return m_Type; }

    float GetSpeed() const { return m_speed; }

    FormationComponent* GetFormation() const { return m_pFormation; }
    void SetFormationPosition(FormationComponent* formation, glm::vec3 posIndex);
    glm::vec3 GetPosIndex() const { return m_PositionIndex; }

    std::vector<glm::vec2>* GetFormationPath(int index) const { return &s_FormationPaths[index]; }
    void SetForamationPath(int path) { m_CurrentFormationPath = path; }
    int GetCurrentFormationPath() const { return m_CurrentFormationPath; }

    virtual std::vector<glm::vec2>* GetAttackingPath(int index) const = 0;
    void SetAttackingPath(int path) { m_AttackingPath = path; }
    int GetCurrentAttackingPath() const { return m_AttackingPath; }

    glm::vec3 GetFormationTargetPosition() const;

    bool GetAbleToAttack() const { return m_AbleToAttack; }
    virtual void SetAbleToAttack(bool ableToAttack);

    void SetAttackSide(int side) { m_AttackSide = side; }

    bool GetIsDiving() const { return m_IsDiving; }
    void SetIsDiving(bool value) { m_IsDiving = value; }

    virtual void TakeDamages(bew::GameObject* pPlayer) = 0;

    //in the EnemyComponent because it needs to be used in the enemyStates
    virtual CaptureBeamComponent* GetCaptureBeam() const { return nullptr; }

    void Shoot();
    bew::GameObject* GetBullet() const { return m_pBullet; }

    virtual ~EnemyComponent() override;
    EnemyComponent(const EnemyComponent& other) = delete;
    EnemyComponent(EnemyComponent&& other) = delete;
    EnemyComponent& operator=(const EnemyComponent& other) = delete;
    EnemyComponent& operator=(EnemyComponent&& other) = delete;
private:
    void CreateBullet();
    void CheckInHitBox();
protected:
    std::vector < bew::GameObject*>* GetPlayer() { return m_pPlayers; }

    void SpawnExplosion();

    EnemyTypes m_Type{};
    std::vector <bew::GameObject*>* m_pPlayers{};
    bew::GameObject* m_pBullet{};

    EnemyStates* m_pStates{};
    FormationComponent* m_pFormation{};

    float m_speed{};
    int m_CurrentFormationPath{0};
    int m_AttackingPath{};

    glm::vec3 m_PositionIndex{};

    bool m_IsDiving{false};
    bool m_AbleToAttack{false};
    int m_AttackSide{};

    int m_AmountPointsFormation{};
    int m_AmountPointsDiving{};

    //static because All enemies need them to be the same exact thing
    static std::vector<std::vector<glm::vec2>> s_FormationPaths;
};

