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
    virtual ~EnemyComponent() override;

    EnemyComponent(const EnemyComponent& other) = delete;
    EnemyComponent(EnemyComponent&& other) = delete;
    EnemyComponent& operator=(const EnemyComponent& other) = delete;
    EnemyComponent& operator=(EnemyComponent&& other) = delete;

    virtual void ResetEnemy();

    void FixedUpdate() override;
    void Update() override;
    void Render() const override;

    virtual void HandelStates();

    float GetSpeed() const { return m_speed; }
    std::vector<glm::vec2>* GetFormationPath(int index) const { return &s_FormationPaths[index]; }
    virtual std::vector<glm::vec2>* GetAttackingPath(int index) const = 0;

    FormationComponent* GetFormation() const { return m_pFormation; }
    int GetCurrentFormationPath() const { return m_CurrentFormationPath; }
    int GetAttackingPathIndex() const { return m_AttackingPath; }

	void SetFormationPosition(FormationComponent* formation, glm::vec3 posIndex);

    glm::vec3 GetFormationTargetPosition() const;

    void SetAttackingPath(int path) { m_AttackingPath = path; }
    void SetForamationPath(int path) { m_CurrentFormationPath = path; }

    void StartAndSetActive();

    EnemyTypes GetEnemyType() const { return m_Type; }

    bool GetAbleToAttack() const { return m_AbleToAttack; }
    virtual void SetAbleToAttack(bool ableToAttack);

    void SetAttackSide(int side) { m_AttackSide = side; }

    bool GetIsDiving() const { return m_IsDiving; }
    ///false is left, true is right
    void SetIsDiving(bool value) { m_IsDiving = value; }

    glm::vec3 GetPosIndex() const { return m_PositionIndex; }

    //I know this shit
    //todo make it better some way
	virtual CaptureBeamComponent* GetCaptureBeam() const { return nullptr; }

    virtual void TakeDamages(bew::GameObject* pPlayer) = 0;

    void Shoot();
    bew::GameObject* GetBullet()const { return m_pBullet; }


private:
    void CreateBullet();
    void CheckInHitBox();
protected:
    std::vector < bew::GameObject*>* GetPlayer() { return m_pPlayers; }

    void SpawnExplosion();
   

    EnemyTypes m_Type{};

    std::vector <bew::GameObject*>* m_pPlayers{};

    EnemyStates* m_States{};

    float m_speed{};
    int m_CurrentFormationPath{0};
    int m_AttackingPath{};

    FormationComponent* m_pFormation{};
    glm::vec3 m_PositionIndex{};

    bool m_IsDiving{false};
    bool m_AbleToAttack{false};
    int m_AttackSide{};

    int m_AmountPointsFormation{};
    int m_AmountPointsDiving{};

    bew::GameObject* m_pBullet{};

    //static because All enemies need them to be the same exact thing
    static std::vector<std::vector<glm::vec2>> s_FormationPaths;
};

